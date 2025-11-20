// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Implementation of TextStructure methods.

#include "verible/common/text/text-structure.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <sstream>  // IWYU pragma: keep  // for ostringstream
#include <string_view>
#include <utility>
#include <vector>

#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "verible/common/strings/line-column-map.h"
#include "verible/common/strings/mem-block.h"
#include "verible/common/text/concrete-syntax-leaf.h"
#include "verible/common/text/concrete-syntax-tree.h"
#include "verible/common/text/symbol.h"
#include "verible/common/text/token-info.h"
#include "verible/common/text/token-stream-view.h"
#include "verible/common/text/tree-utils.h"
#include "verible/common/util/iterator-range.h"
#include "verible/common/util/logging.h"
#include "verible/common/util/range.h"
#include "verible/common/util/status-macros.h"
#include "verilog-nonterminals.h"
#include "verilog-token-enum.h"

namespace verible {

TextStructureView::TextStructureView(std::string_view contents)
    : contents_(contents) {
  // more than sufficient memory as number-of-tokens <= bytes-in-file,
  // push_back() should never re-alloc because size <= initial capacity.
  tokens_.reserve(contents.length());
  const absl::Status status = InternalConsistencyCheck();
  CHECK(status.ok())
      << "Failed internal iterator/string_view consistency check in ctor:\n  "
      << status.message();
}


void take_all_tokens(slang::syntax::SyntaxNode& root_slang, 
                     std::vector<slang::parsing::Token> &tokens_container);


void special_case_handling(slang::syntax::SyntaxNode& root_slang, 
                           verible::SyntaxTreeNode &root_verible,
   std::string_view contents, std::vector<TokenInfo> &tokens_);

void find_trivia(slang::parsing::Trivia trivia, 
                 verible::SyntaxTreeNode &root_verible, 
                 slang::SourceManager &sm, std::string_view contents, std::vector<TokenInfo> &tokens);

verible::SyntaxTreeNode& find_tokens(slang::syntax::SyntaxNode& root_slang, 
                                     verible::SyntaxTreeNode& root_verible, 
                                     slang::SourceManager &sm, std::string_view contents, std::vector<TokenInfo> &tokens);

std::unique_ptr<verible::SyntaxTreeNode> tree_transformation_from_slang_to_verible(
    std::shared_ptr<slang::syntax::SyntaxTree> tree, 
    slang::SourceManager &sm, std::string_view contents, std::vector<TokenInfo> &tokens);


/*нужна особая обработка случая ImplicitAnsiPort, у сланга и у верибла разные структуры*/


/*node tag: 2         node : CompilationUnit                         
node tag: 48          node : SyntaxList  node : ModuleDeclaration
node tag: 49          node : SyntaxList node : ModuleHeader
token tag: 360        token : ModuleKeyword
token tag: 293        token : Identifier
node tag: 65          node : SyntaxList  node : AnsiPortList
token tag: 40         token : OpenParenthesis
node tag: 290         node : SeparatedList  

//особая обработка ImplicitAnsiPort
node tag: 291   kPortDeclaration     node :ImplicitAnsiPort  node : SyntaxList  node : VariablePortHeader
token tag: 354  TK_input             token : InputKeyword
node tag: 128   kDataType            node : ImplicitType
node tag: 47    kUnqualifiedId       node : SyntaxList token : Placeholder node : Declarator 
token tag: 293  SymbolIdentifier     token : Identifier
node tag: 266   kUnpackedDimensions  вычислить самому 
        
token tag: 44        node : SyntaxList token : Comma


//особая обработка ImplicitAnsiPort     если нет input или output то node : ImplicitType уходит в никуда
node tag: 103  kPort                node : ImplicitAnsiPort node : SyntaxList node : VariablePortHeader
node tag: 106  kPortReference       node : ImplicitType 
node tag: 47   kUnqualifiedId       node : SyntaxList token : Placeholder node : Declarator //тут остановился
token tag: 293 SymbolIdentifier     token : Identifier

token tag: 44        node : SyntaxList  token : Comma


//особая обработка ImplicitAnsiPort
node tag: 291       node : ImplicitAnsiPort   node : SyntaxList  node : VariablePortHeader
token tag: 370      token : OutputKeyword
node tag: 128       node : ImplicitType
node tag: 47        node : SyntaxList token : Placeholder node : Declarator
token tag: 293      token : Identifier
node tag: 266       вычислить самому


token tag: 41       node : SyntaxList   token : CloseParenthesis
token tag: 59       token : Semicolon


node tag: 292  kModuleItemList      node : SyntaxList
token tag: 337 TK_endmodule         token : EndModuleKeyword
node tag: 257  kLabel               node : NamedBlockClause
token tag: 58                       token : Colon
token tag: 293 SymbolIdentifier     token : Identifier    token : EndOfFile
*/


static std::unordered_map<slang::syntax::SyntaxKind, verilog::NodeEnum> node_slang_to_verible = {
    {slang::syntax::SyntaxKind::CompilationUnit, verilog::NodeEnum::kDescriptionList},
    {slang::syntax::SyntaxKind::ModuleDeclaration, verilog::NodeEnum::kModuleDeclaration},
    {slang::syntax::SyntaxKind::ModuleHeader, verilog::NodeEnum::kModuleHeader},
    {slang::syntax::SyntaxKind::AnsiPortList, verilog::NodeEnum::kParenGroup},
    {slang::syntax::SyntaxKind::SeparatedList, verilog::NodeEnum::kPortDeclarationList},
    {slang::syntax::SyntaxKind::Declarator, verilog::NodeEnum::kUnqualifiedId},
    {slang::syntax::SyntaxKind::NamedBlockClause, verilog::NodeEnum::kLabel},   
};

static std::unordered_map<slang::parsing::TokenKind, int> token_slang_to_verible = {
    {slang::parsing::TokenKind::ModuleKeyword, verilog_tokentype::TK_module},
    {slang::parsing::TokenKind::Identifier, verilog_tokentype::SymbolIdentifier},
    {slang::parsing::TokenKind::OpenParenthesis, 40},
    {slang::parsing::TokenKind::CloseParenthesis, 41},
    {slang::parsing::TokenKind::InputKeyword, verilog_tokentype::TK_input},
    {slang::parsing::TokenKind::OutputKeyword, verilog_tokentype::TK_output},
    {slang::parsing::TokenKind::Comma, 44},
    {slang::parsing::TokenKind::Semicolon, 59},
    {slang::parsing::TokenKind::EndModuleKeyword, verilog_tokentype::TK_endmodule},
    {slang::parsing::TokenKind::Colon, 58},
};



void take_all_tokens(slang::syntax::SyntaxNode& root_slang, std::vector<slang::parsing::Token> &tokens_container){
    slang::size_t count_child = root_slang.getChildCount();
    for (slang::size_t i = 0; i < count_child; i++) {

        if (auto childNode = root_slang.childNode(i); childNode) {
            take_all_tokens(*childNode, tokens_container);
        }
        else if (auto token = root_slang.childToken(i); token) {
            if(!(token.kind == slang::parsing::TokenKind::Placeholder || token.kind == slang::parsing::TokenKind::EndOfFile)){
                tokens_container.push_back(token);
            }
        }
    }
}

void special_case_handling(slang::syntax::SyntaxNode& root_slang, verible::SyntaxTreeNode &root_verible,
   std::string_view contents, std::vector<TokenInfo> &tokens_){
    if(root_slang.kind == slang::syntax::SyntaxKind::ImplicitAnsiPort){
      std::vector<slang::parsing::Token> tokens;
      take_all_tokens(root_slang,tokens);
      auto input_or_output = std::find_if(tokens.begin(), tokens.end(), 
                           [&](const slang::parsing::Token& elem){ 
                               return elem.kind == slang::parsing::TokenKind::InputKeyword
                               || elem.kind == slang::parsing::TokenKind::OutputKeyword; 
                           });
      if(input_or_output != tokens.end()){
        auto new_node = std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kPortDeclaration);
        //std::cerr << "node " << new_node->Tag().tag << "\n";
        auto tag = token_slang_to_verible.find(input_or_output->kind) -> second;
        
        auto start = input_or_output->location().offset();
        auto len   = input_or_output->rawText().size();
        std::string_view sv(contents.data() + start, len);

        auto token_info = TokenInfo(tag, sv);
        tokens_.push_back(token_info);        
        new_node->AppendChild(std::make_unique<verible::SyntaxTreeLeaf>(token_info));
        //std::cerr << "token " << tag << "\n";
        new_node->AppendChild(std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kDataType));
        //std::cerr << "node " << (int)verilog::NodeEnum::kDataType << "\n";
        
        auto identifier = tokens[1];
        auto start2 = identifier.location().offset();
        auto len2   = identifier.rawText().size();
        std::string_view sv2(contents.data() + start2, len2);

        auto tok_info = TokenInfo(verilog_tokentype::SymbolIdentifier, sv2);
        tokens_.push_back(tok_info); 
        auto new_nod = std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kUnqualifiedId);
        new_nod->AppendChild(std::make_unique<verible::SyntaxTreeLeaf>(tok_info));
        //std::cerr << "node " << new_nod->Tag().tag << "\n";
        //std::cerr << "token " << (int)verilog_tokentype::SymbolIdentifier << "\n";
        
        new_node->AppendChild(std::move(new_nod));
        new_node->AppendChild(std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kUnpackedDimensions));
        //std::cerr << "node " << (int)verilog::NodeEnum::kUnpackedDimensions << "\n";
        
        root_verible.AppendChild(std::move(new_node));
      }
      else{
        auto new_node = std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kPort);
        //std::cerr << "node " << new_node->Tag().tag << "\n";
        auto new_nod = std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kPortReference);
        //std::cerr << "node " << new_nod->Tag().tag << "\n";
        
        auto identifier = tokens[0];
        auto start = identifier.location().offset();
        auto len   = identifier.rawText().size();
        std::string_view sv2(contents.data() + start, len);

        auto tok_info = TokenInfo(verilog_tokentype::SymbolIdentifier, sv2);
        tokens_.push_back(tok_info); 
        auto new_n = std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kUnqualifiedId);
        //std::cerr << "node " << new_n->Tag().tag << "\n";
        new_n->AppendChild(std::make_unique<verible::SyntaxTreeLeaf>(tok_info));
        //std::cerr << "token " << (int)verilog_tokentype::SymbolIdentifier << "\n";
        
        new_nod->AppendChild(std::move(new_n));
        new_node->AppendChild(std::move(new_nod));
        root_verible.AppendChild(std::move(new_node));
      }
    }
}


//using slang parcer
TextStructureView::TextStructureView(std::string_view contents, std::shared_ptr<slang::syntax::SyntaxTree> tree, slang::SourceManager &sm)
  : contents_(contents){
    std::vector<TokenInfo> tokens;
    syntax_tree_ =  tree_transformation_from_slang_to_verible(tree, sm, contents_,tokens);
    tokens.push_back(EOFToken());
    tokens_ = tokens;
    
    tokens_view_.reserve(tokens_.size());
    for (auto it = tokens_.cbegin(); it != tokens_.cend(); ++it) {
        tokens_view_.push_back(it);
    }
}


void find_trivia(slang::parsing::Trivia trivia, verible::SyntaxTreeNode &root_verible,
   slang::SourceManager &sm, std::string_view contents, std::vector<TokenInfo> &tokens){
    if (trivia.kind == slang::parsing::TriviaKind::LineComment || trivia.kind == slang::parsing::TriviaKind::BlockComment) {
                
    }
    if(trivia.kind == slang::parsing::TriviaKind::Directive) {
        auto& syntax = *trivia.syntax();
        find_tokens(syntax, root_verible, sm, contents,tokens);
    }
    if(trivia.kind == slang::parsing::TriviaKind::SkippedSyntax){
        find_tokens(*trivia.syntax(), root_verible, sm, contents, tokens);
    }
    if(trivia.kind == slang::parsing::TriviaKind::SkippedTokens){
                        
      for (slang::parsing::Token t : trivia.getSkippedTokens()){
      }
    }
    if(trivia.kind == slang::parsing::TriviaKind::DisabledText){
    }
}


verible::SyntaxTreeNode& find_tokens(slang::syntax::SyntaxNode& root_slang, verible::SyntaxTreeNode& root_verible,
   slang::SourceManager &sm, std::string_view contents, std::vector<TokenInfo> &tokens) {

    verible::SyntaxTreeNode* new_node = &root_verible;


    if(root_slang.kind != slang::syntax::SyntaxKind::SyntaxList){
      auto find_in_table = node_slang_to_verible.find(root_slang.kind);
      if(find_in_table != node_slang_to_verible.end()){
        auto tag = find_in_table->second;
        auto new_node_ptr = std::make_unique<verible::SyntaxTreeNode>((int)tag);
        verible::SyntaxTreeNode& new_node_ref = *new_node_ptr;
        root_verible.AppendChild(std::move(new_node_ptr));
        new_node = &new_node_ref;
        //std::cerr << "node " << new_node->Tag().tag << "\n";
      }
      else{
        special_case_handling(root_slang,root_verible,contents,tokens);
        return *new_node;
      }
    }

    slang::size_t count_child = root_slang.getChildCount();
   
    for (slang::size_t i = 0; i < count_child; i++) {


        if (auto childNode = root_slang.childNode(i); childNode) {
            find_tokens(*childNode,*new_node, sm, contents, tokens);
        }
        else if (auto token = root_slang.childToken(i); token) {
            if(sm.isIncludedFileLoc(token.location())){
                continue;
            }

            slang::SmallVector<const slang::parsing::Trivia*> pending;
            for (const auto& trivia : token.trivia()) {
                pending.push_back(&trivia);
                auto loc = trivia.getExplicitLocation();
                if (loc) {
                    if (!sm.isIncludedFileLoc(*loc)) {
                        for (auto t : pending)
                            find_trivia(*t, *new_node, sm, contents, tokens);
                    }
                    else {
                        if (trivia.kind == slang::parsing::TriviaKind::Directive ||
                            trivia.kind == slang::parsing::TriviaKind::SkippedSyntax ||
                            trivia.kind == slang::parsing::TriviaKind::SkippedTokens) {
                            find_trivia(trivia, *new_node,sm, contents, tokens);
                        }
                    }
                    pending.clear();
                }
            }

            for (auto t : pending){
                find_trivia(*t, *new_node, sm, contents, tokens);
            }
            if(sm.isMacroLoc(token.location())){
                continue;
            }
            //костыль
            if(token.kind == slang::parsing::TokenKind::EndModuleKeyword){
              root_verible.AppendChild(std::make_unique<verible::SyntaxTreeNode>((int)verilog::NodeEnum::kModuleItemList));
              //std::cerr << "node " << (int)verilog::NodeEnum::kModuleItemList << "\n";
            }
            if(token.kind == slang::parsing::TokenKind::EndOfFile){
              continue;
            }

            auto find_in_table = token_slang_to_verible.find(token.kind);
            if(find_in_table != token_slang_to_verible.end()){

                auto tag = find_in_table->second;
                auto start = token.location().offset();
                auto length = token.rawText().size();
                std::string_view sv(contents.data() + start, length);
                auto token_info = TokenInfo(tag,sv);
                new_node->AppendChild(std::make_unique<verible::SyntaxTreeLeaf>(token_info));
                tokens.push_back(token_info);
                //std::cerr << "token " << tag << "\n";
            }
        }
    }
    return *new_node;
}


std::unique_ptr<verible::SyntaxTreeNode> tree_transformation_from_slang_to_verible(std::shared_ptr<slang::syntax::SyntaxTree> tree,
   slang::SourceManager &sm, std::string_view contents, std::vector<TokenInfo> &tokens){
  auto root_verible = std::make_unique<verible::SyntaxTreeNode>();
  auto& child_node = find_tokens(tree->root(), *root_verible, sm, contents, tokens);
  return std::make_unique<verible::SyntaxTreeNode>(std::move(child_node));
}

TextStructureView::~TextStructureView() {
  const absl::Status status = InternalConsistencyCheck();
  CHECK(status.ok())
      << "Failed internal iterator/string_view consistency check in dtor:\n  "
      << status.message();
}

void TextStructureView::Clear() {
  syntax_tree_ = nullptr;
  lazy_lines_info_.valid = false;
  lazy_line_token_map_.clear();
  tokens_view_.clear();
  tokens_.clear();
  contents_ = contents_.substr(0, 0);  // clear
}

static bool TokenLocationLess(const TokenInfo &token,
                              const std::string_view::const_iterator offset) {
  return token.text().begin() < offset;
}

// Makes an iterator-writable copy of items_view without using const_cast.
template <class V>
static std::vector<typename V::iterator> CopyWriteableIterators(
    V &items, const std::vector<typename V::const_iterator> &items_view) {
  // precondition: items_view's iterators all point into items array.
  // postcondition: results's iterators point to the same items as items_view.
  std::vector<typename V::iterator> result;
  result.reserve(items_view.size());
  typename V::iterator iter(items.begin());
  const typename V::const_iterator const_iter(items.begin());
  for (auto view_iter : items_view) {
    result.push_back(iter + std::distance(const_iter, view_iter));
  }
  return result;
}

TokenStreamReferenceView TextStructureView::MakeTokenStreamReferenceView() {
  return CopyWriteableIterators(tokens_, tokens_view_);
}

const std::vector<TokenSequence::const_iterator> &
TextStructureView::GetLineTokenMap() const {
  // Lazily calculate the map. It is mutable, so we can modify it here.
  if (lazy_line_token_map_.empty()) {
    auto token_iter = tokens_.cbegin();
    const auto &offset_map = GetLineColumnMap().GetBeginningOfLineOffsets();
    for (const auto offset : offset_map) {
      // TODO(fangism): linear search might be as competitive as binary search
      token_iter =
          std::lower_bound(token_iter, tokens_.cend(),
                           Contents().begin() + offset, &TokenLocationLess);
      lazy_line_token_map_.push_back(token_iter);
    }
    // Add an end() iterator so map has N+1 entries.
    // When there is no newline on the last line, this value will be different
    // from the previous iterator's index.
    lazy_line_token_map_.push_back(tokens_.cend());
  }

  return lazy_line_token_map_;
}

TokenRange TextStructureView::TokenRangeSpanningOffsets(size_t lower,
                                                        size_t upper) const {
  const auto text_base = Contents().begin();
  // Range is found with two binary searches.
  // TODO(fangism): Is there a way to make this work with a single call
  // to std::equal_range()?
  const auto left = std::lower_bound(tokens_.cbegin(), tokens_.cend(),
                                     text_base + lower, &TokenLocationLess);
  const auto right = std::lower_bound(left, tokens_.cend(), text_base + upper,
                                      &TokenLocationLess);
  return make_range(left, right);
}

LineColumnRange TextStructureView::GetRangeForToken(
    const TokenInfo &token) const {
  if (token.isEOF()) {
    // In particular some unit tests pass in an artificial EOF token, not a
    // EOF token generated from this view. So handle this directly.
    const LineColumn eofPos = GetLineColAtOffset(Contents().length());
    return {eofPos, eofPos};
  }
  // TODO(hzeller): This should simply be GetRangeForText(token.text()),
  // but the more thorough error checking in GetRangeForText()
  // exposes a token overrun in verilog_analyzer_test.cc
  // Defer to fix in separate change.
  return {GetLineColAtOffset(token.left(Contents())),
          GetLineColAtOffset(token.right(Contents()))};
}

LineColumnRange TextStructureView::GetRangeForText(
    std::string_view text) const {
  const auto from = std::distance(Contents().begin(), text.begin());
  const auto to = std::distance(Contents().begin(), text.end());
  CHECK_GE(from, 0) << '"' << text << '"';
  CHECK_LE(to, static_cast<int64_t>(Contents().length())) << '"' << text << '"';
  return {GetLineColAtOffset(from), GetLineColAtOffset(to)};
}

bool TextStructureView::ContainsText(std::string_view text) const {
  return IsSubRange(text, Contents());
}

TokenRange TextStructureView::TokenRangeOnLine(size_t lineno) const {
  const auto &line_token_map = GetLineTokenMap();
  if (lineno + 1 < line_token_map.size()) {
    return make_range(line_token_map[lineno], line_token_map[lineno + 1]);
  }
  return make_range(tokens_.cend(), tokens_.cend());
}

TokenInfo TextStructureView::FindTokenAt(const LineColumn &pos) const {
  if (pos.line < 0 || pos.column < 0) return EOFToken();
  // Maybe do binary search here if we have a huge amount tokens per line.
  for (const TokenInfo &token : TokenRangeOnLine(pos.line)) {
    if (GetRangeForToken(token).PositionInRange(pos)) return token;
  }
  return EOFToken();
}

TokenInfo TextStructureView::EOFToken() const {
  return TokenInfo::EOFToken(Contents());
}

// Removes tokens from the TokenStreamView that do not satisfy the keep
// predicate.
void TextStructureView::FilterTokens(const TokenFilterPredicate &keep) {
  FilterTokenStreamViewInPlace(keep, &tokens_view_);
}

static void TerminateTokenStream(TokenSequence *tokens) {
  if (tokens->empty()) return;
  if (tokens->back().isEOF()) return;
  // push_back might cause re-alloc.
  tokens->push_back(TokenInfo::EOFToken(tokens->back().text()));
}

void TextStructureView::FocusOnSubtreeSpanningSubstring(int left_offset,
                                                        int length) {
  VLOG(2) << __FUNCTION__ << " at " << left_offset << " +" << length;
  const int right_offset = left_offset + length;
  TrimSyntaxTree(left_offset, right_offset);

  // Don't let the syntax tree be empty.
  // Always return a tree with one node.
  // This can happen when TrimSyntaxTree() yields a nullptr syntax tree
  if (syntax_tree_ == nullptr) {
    syntax_tree_ = MakeNode();
  }
  TrimTokensToSubstring(left_offset, right_offset);
  TrimContents(left_offset, length);
  lazy_lines_info_.valid = false;
  CalculateFirstTokensPerLine();
  const absl::Status status = InternalConsistencyCheck();
  CHECK(status.ok())
      << "Failed internal iterator/string_view consistency check:\n  "
      << status.message();
  VLOG(2) << "end of " << __FUNCTION__;
}

// Replace the syntax_tree_ field with the largest subtree wholly contained
// inside the offset bounds.
// Discards nodes outside of the referenced subtree.
void TextStructureView::TrimSyntaxTree(int first_token_offset,
                                       int last_token_offset) {
  const std::string_view text_range(Contents().substr(
      first_token_offset, last_token_offset - first_token_offset));
  verible::TrimSyntaxTree(&syntax_tree_, text_range);
}

// Reduces the set of tokens to that spanned by [left_offset, right_offset).
// The resulting token stream is terminated with an EOF token, whose range
// reflects the right_offset.
void TextStructureView::TrimTokensToSubstring(int left_offset,
                                              int right_offset) {
  VLOG(2) << __FUNCTION__ << " [" << left_offset << ',' << right_offset << ')';
  // Find first token that starts at or after the offset.  (binary_search)
  // Find first token that starts beyond the syntax tree.  (binary_search)
  const auto view_trim_range =
      TokenRangeSpanningOffsets(left_offset, right_offset);
  CHECK(tokens_.begin() <= view_trim_range.begin());
  CHECK(view_trim_range.begin() <= view_trim_range.end());
  CHECK(view_trim_range.end() <= tokens_.end());

  // Find the view iterators that fall within this range.
  const auto iter_trim_begin = std::lower_bound(
      tokens_view_.begin(), tokens_view_.end(), view_trim_range.begin());
  const auto iter_trim_end = std::lower_bound(
      iter_trim_begin, tokens_view_.end(), view_trim_range.end());

  // Copy subset of tokens to new token sequence.
  TokenSequence trimmed_stream(view_trim_range.begin(), view_trim_range.end());

  // If the last token straddles the end-of-range, (possibly due to lexical
  // error), then trim its tail, bounded by right_offset.
  if (!trimmed_stream.empty()) {
    const std::string_view substr(
        contents_.substr(left_offset, right_offset - left_offset));
    TokenInfo &last(trimmed_stream.back());
    const int overhang = std::distance(substr.end(), last.text().end());
    if (!IsSubRange(last.text(), substr)) {
      VLOG(2) << "last token overhangs end by " << overhang << ": " << last;
      std::string_view trimmed_tail_token(last.text());
      trimmed_tail_token.remove_suffix(overhang);
      last.set_text(trimmed_tail_token);
      // TODO(fangism): Should the token enum be set to some error value,
      // if it is not already an error value?
    }
  }

  TerminateTokenStream(&trimmed_stream);  // Append EOF token.

  // Recalculate iterators for new token stream view, pointing into new
  // token sequence.
  const int index_difference =
      std::distance(tokens_.cbegin(), view_trim_range.begin());
  TokenStreamView trimmed_view;
  trimmed_view.reserve(std::distance(iter_trim_begin, iter_trim_end));
  for (auto token_iterator : make_range(iter_trim_begin, iter_trim_end)) {
    const int old_index = std::distance(tokens_.cbegin(), token_iterator);
    const int new_index = old_index - index_difference;
    trimmed_view.push_back(trimmed_stream.begin() + new_index);
  }

  // Swap new-old arrays, which will cause old arrays to be deleted.
  tokens_view_.swap(trimmed_view);
  tokens_.swap(trimmed_stream);
}

void TextStructureView::TrimContents(int left_offset, int length) {
  contents_ = contents_.substr(left_offset, length);
}

const TextStructureView::LinesInfo &TextStructureView::LinesInfo::Get(
    std::string_view contents) {
  if (valid) return *this;

  lines = absl::StrSplit(contents, '\n');
  line_column_map.reset(new LineColumnMap(lines));
  valid = true;

  return *this;
}

void TextStructureView::RebaseTokensToSuperstring(std::string_view superstring,
                                                  std::string_view src_base,
                                                  int offset) {
  MutateTokens([&](TokenInfo *token) {
    const int delta = token->left(src_base);
    // Superstring must point to separate memory space.
    token->RebaseStringView(superstring.begin() + offset + delta);
  });
  // Assigning superstring for the sake of maintaining range invariants.
  contents_ = superstring;
  lazy_lines_info_.valid = false;
}

void TextStructureView::MutateTokens(const LeafMutator &mutator) {
  for (auto &token : tokens_) {
    mutator(&token);
  }
  // No need to touch tokens_view_, all transformations are in-place.

  if (syntax_tree_ != nullptr) {
    // The tokens at the leaves of the tree are their own copies, and thus
    // need to re-apply the same transformation.
    MutateLeaves(&syntax_tree_, mutator);
  }
}

// Find the last non-EOF token.  Usually searches at most 2 tokens.
static const TokenInfo *FindLastNonEOFToken(const TokenSequence &tokens) {
  const auto iter =
      std::find_if(tokens.rbegin(), tokens.rend(),
                   [](const TokenInfo &token) { return !token.isEOF(); });
  return iter != tokens.rend() ? &*iter : nullptr;
}

absl::Status TextStructureView::FastTokenRangeConsistencyCheck() const {
  VLOG(2) << __FUNCTION__;
  // Check the ranges of the first and last element of the critical arrays.
  // A more thorough full-check would scan every single token.
  const auto lower_bound = contents_.begin();
  const auto upper_bound = contents_.end();
  if (!tokens_.empty()) {
    // Check that extremities of first and last token lie inside contents_.
    const TokenInfo &first = tokens_.front();
    if (!first.isEOF() && lower_bound > first.text().cbegin()) {
      return absl::InternalError(absl::StrCat(
          "Token offset points before beginning of string contents.  delta=",
          std::distance(first.text().cbegin(), lower_bound)));
    }
    const TokenInfo *last = FindLastNonEOFToken(tokens_);
    if (last != nullptr && last->text().cend() > upper_bound) {
      return absl::InternalError(absl::StrCat(
          "Token offset points past end of string contents.  delta=",
          std::distance(upper_bound, last->text().cend())));
    }
    if (!tokens_view_.empty()) {
      // Check that TokenSequence iterators point into tokens_.
      if (tokens_.begin() > tokens_view_.front()) {
        return absl::InternalError(
            "First token iterator points before beginning of array.");
      }
      if (tokens_view_.front() >= tokens_.end()) {
        return absl::InternalError(
            "First token iterator points past end of array.");
      }
      if (tokens_.begin() > tokens_view_.back()) {
        return absl::InternalError(
            "Last token iterator points before beginning of array.");
      }
      if (tokens_view_.back() >= tokens_.end()) {
        return absl::InternalError(
            "Last token iterator points past end of array.");
      }
    }
    if (!lazy_line_token_map_.empty()) {
      if (lazy_line_token_map_.front() != tokens_.begin()) {
        return absl::InternalError(
            "Per-line token iterator map does not start with the beginning of "
            "the token sequence.");
      }
      if (lazy_line_token_map_.back() != tokens_.end()) {
        return absl::InternalError(
            "Per-line token iterator map does not end with to the end of the "
            "token sequence.");
      }
    }
  }
  return absl::OkStatus();
}

absl::Status TextStructureView::FastLineRangeConsistencyCheck() const {
  VLOG(2) << __FUNCTION__;
  const auto &lines = Lines();
  if (!lines.empty()) {
    if (lines.front().cbegin() != contents_.cbegin()) {
      return absl::InternalError(
          "First line does not match beginning of text.");
    }
    if (lines.back().cend() != contents_.cend()) {
      return absl::InternalError("Last line does not match end of text.");
    }
  }
  return absl::OkStatus();
}

absl::Status TextStructureView::SyntaxTreeConsistencyCheck() const {
  VLOG(2) << __FUNCTION__;
  // Check that first and last token in syntax_tree_ point to text
  // inside contents_.
  const std::string_view::const_iterator lower_bound = contents_.begin();
  const std::string_view::const_iterator upper_bound =
      lower_bound + contents_.length();
  if (syntax_tree_ != nullptr) {
    const SyntaxTreeLeaf *left = GetLeftmostLeaf(*syntax_tree_);
    if (!left) return absl::OkStatus();
    const SyntaxTreeLeaf *right = GetRightmostLeaf(*syntax_tree_);
    if (lower_bound > left->get().text().cbegin()) {
      return absl::InternalError(
          "Left-most tree leaf points before beginning of contents.");
    }
    if (right->get().text().cend() > upper_bound) {
      return absl::InternalError(
          "Right-most tree leaf points past end of contents.");
    }
  }
  return absl::OkStatus();
}

absl::Status TextStructureView::InternalConsistencyCheck() const {
  RETURN_IF_ERROR(FastLineRangeConsistencyCheck());
  RETURN_IF_ERROR(FastTokenRangeConsistencyCheck());
  return SyntaxTreeConsistencyCheck();
}

// "token_source" is a sequence of tokens.
// The TokenRange can be a container reference or iterator range.
//
// "view_source" is a sequence of iterators pointing to token_source content.
// The TokenViewRange can be a container reference or iterator range.
template <typename TokenRange, typename TokenViewRange>
static void CopyTokensAndView(TokenSequence *destination,
                              std::vector<int> *view_indices,
                              const TokenRange &token_source,
                              const TokenViewRange &view_source) {
  // Translate token_view's iterators into array indices, adjusting for the
  // number of pre-existing tokens.
  const auto pre_existing_start_index = destination->size();
  for (const auto &token_iter : view_source) {
    // TODO: something is wrong here, the view should never have iterators
    // pointing outside the range of the source. Needs to be explored.
#if 0
    CHECK(token_iter >= token_source.begin() &&
          token_iter < token_source.end());
#endif
    view_indices->push_back(pre_existing_start_index +
                            std::distance(token_source.begin(), token_iter));
  }
  // Copy tokens up to this expansion point.
  for (const auto &token : token_source) {
    destination->push_back(token);
  }
}

// Incrementally copies a slice of tokens and expands a single subtree.
// This advances the next_token_iter and next_token_view_iter iterators.
// The subtree from the expansion is transferred into this objects's syntax
// tree.  Indices into the final token stream view are collected in
// token_view_indices.  Offset is the location of each expansion point.
void TextStructureView::ConsumeDeferredExpansion(
    TokenSequence::const_iterator *next_token_iter,
    TokenStreamView::const_iterator *next_token_view_iter,
    DeferredExpansion *expansion, TokenSequence *combined_tokens,
    std::vector<int> *token_view_indices,
    std::string_view::const_iterator offset) {
  auto token_iter = *next_token_iter;
  auto token_view_iter = *next_token_view_iter;
  // Find the position up to each expansion point.
  *next_token_iter = std::lower_bound(
      token_iter, tokens_.cend(), offset,
      [](const TokenInfo &token, std::string_view::const_iterator target) {
        return std::distance(target, token.text().begin()) < 0;
      });
  CHECK(*next_token_iter != tokens_.cend());
  *next_token_view_iter = std::lower_bound(
      token_view_iter, tokens_view_.cend(), offset,
      [](TokenStreamView::const_reference token_ref,
         std::string_view::const_iterator target) {
        return std::distance(target, token_ref->text().begin()) < 0;
      });
  CHECK(*next_token_view_iter != tokens_view_.cend());

  // Copy tokens and partial view into output.
  CopyTokensAndView(combined_tokens, token_view_indices,
                    make_range(token_iter, *next_token_iter),
                    make_range(token_view_iter, *next_token_view_iter));

  // Adjust locations of tokens in the expanded tree by pointing them
  // into the original text (contents_).
  std::unique_ptr<TextStructure> &subanalysis = expansion->subanalysis;
  TextStructureView &sub_data = ABSL_DIE_IF_NULL(subanalysis)->MutableData();
  const std::string_view sub_data_text(sub_data.Contents());
  CHECK(!IsSubRange(sub_data_text, contents_));
  CHECK_EQ(sub_data_text, std::string_view(&*offset, sub_data_text.length()));
  CHECK(offset >= contents_.begin());
  sub_data.RebaseTokensToSuperstring(contents_, sub_data_text,
                                     std::distance(contents_.begin(), offset));

  // Translate token_view's iterators into array indices.
  if (!sub_data.tokens_.empty() && sub_data.tokens_.back().isEOF()) {
    // Remove auxiliary data's end-token sentinel before copying.
    // Don't want to splice it into result.
    sub_data.tokens_.pop_back();
  }
  CopyTokensAndView(combined_tokens, token_view_indices, sub_data.tokens_,
                    sub_data.tokens_view_);

  // Transfer ownership of transformed syntax tree to this object's tree.
  *expansion->expansion_point = std::move(sub_data.MutableSyntaxTree());
  subanalysis->MutableData().Clear();

  // Advance one past expansion point to skip over expanded token.
  ++*next_token_iter;
  ++*next_token_view_iter;
}

TextStructure::TextStructure(std::shared_ptr<MemBlock> contents)
    : contents_(std::move(contents)), data_(contents_->AsStringView()) {
  // Internal string_view must point to memory owned by contents_.
  const absl::Status status = InternalConsistencyCheck();
  CHECK(status.ok()) << status.message() << " (in ctor)";
}

TextStructure::TextStructure(std::string_view contents)
    : TextStructure(std::make_shared<StringMemBlock>(contents)) {}

TextStructure::~TextStructure() {
  const absl::Status status = StringViewConsistencyCheck();
  CHECK(status.ok()) << status.message() << " (in dtor)";
}

void TextStructureView::ExpandSubtrees(NodeExpansionMap *expansions) {
  TokenSequence combined_tokens;
  // Gather indices and reconstruct iterators after there are no more
  // reallocations due to growing combined_tokens.
  std::vector<int> combined_token_view_indices;
  auto token_iter = tokens_.cbegin();
  auto token_view_iter = tokens_view_.cbegin();
  for (auto &expansion_entry : *expansions) {
    const auto offset = Contents().begin() + expansion_entry.first;
    ConsumeDeferredExpansion(&token_iter, &token_view_iter,
                             &expansion_entry.second, &combined_tokens,
                             &combined_token_view_indices, offset);
  }

  // Copy the remaining tokens beyond the last expansion point.
  CopyTokensAndView(&combined_tokens, &combined_token_view_indices,
                    make_range(token_iter, tokens_.cend()),
                    make_range(token_view_iter, tokens_view_.cend()));

  // Commit the newly expanded sequence of tokens.
  tokens_.swap(combined_tokens);

  // Reconstruct view iterators from indices into the new sequence.
  tokens_view_.clear();
  tokens_view_.reserve(combined_token_view_indices.size());
  for (const auto index : combined_token_view_indices) {
    tokens_view_.push_back(tokens_.cbegin() + index);
  }

  // Recalculate line-by-line token ranges.
  // TODO(fangism): Should be possible to update line_token_map_ incrementally
  // as well.
  CalculateFirstTokensPerLine();
}

absl::Status TextStructure::StringViewConsistencyCheck() const {
  const std::string_view contents = data_.Contents();
  if (!contents.empty() && !IsSubRange(contents, contents_->AsStringView())) {
    return absl::InternalError(
        "string_view contents_ is not a substring of contents_, "
        "contents_ might reference deallocated memory!");
  }
  return absl::OkStatus();
}

absl::Status TextStructure::InternalConsistencyCheck() const {
  RETURN_IF_ERROR(StringViewConsistencyCheck());
  return data_.InternalConsistencyCheck();
}

}  // namespace verible
