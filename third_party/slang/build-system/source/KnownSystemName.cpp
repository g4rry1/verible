//------------------------------------------------------------------------------
// KnownSystemName.cpp
// Generated KnownSystemName enum
//
// SPDX-FileCopyrightText: Michael Popoloski
// SPDX-License-Identifier: MIT
//------------------------------------------------------------------------------
#include "slang/parsing/KnownSystemName.h"

#include "slang/util/FlatMap.h"

namespace slang::parsing {

std::ostream& operator<<(std::ostream& os, KnownSystemName ksn) {
    os << toString(ksn);
    return os;
}

std::string_view toString(KnownSystemName ksn) {
    switch (ksn) {
        case KnownSystemName::Unknown: return "Unknown";
        case KnownSystemName::Bits: return "$bits";
        case KnownSystemName::Typename: return "$typename";
        case KnownSystemName::IsUnbounded: return "$isunbounded";
        case KnownSystemName::Low: return "$low";
        case KnownSystemName::High: return "$high";
        case KnownSystemName::Left: return "$left";
        case KnownSystemName::Right: return "$right";
        case KnownSystemName::Size: return "$size";
        case KnownSystemName::Increment: return "$increment";
        case KnownSystemName::Dimensions: return "$dimensions";
        case KnownSystemName::UnpackedDimensions: return "$unpacked_dimensions";
        case KnownSystemName::Rtoi: return "$rtoi";
        case KnownSystemName::Itor: return "$itor";
        case KnownSystemName::RealToBits: return "$realtobits";
        case KnownSystemName::BitsToReal: return "$bitstoreal";
        case KnownSystemName::ShortrealToBits: return "$shortrealtobits";
        case KnownSystemName::BitsToShortreal: return "$bitstoshortreal";
        case KnownSystemName::Signed: return "$signed";
        case KnownSystemName::Unsigned: return "$unsigned";
        case KnownSystemName::CoverageControl: return "$coverage_control";
        case KnownSystemName::CoverageGetMax: return "$coverage_get_max";
        case KnownSystemName::CoverageGet: return "$coverage_get";
        case KnownSystemName::CoverageMerge: return "$coverage_merge";
        case KnownSystemName::CoverageSave: return "$coverage_save";
        case KnownSystemName::GetCoverage: return "$get_coverage";
        case KnownSystemName::SetCoverageDbName: return "$set_coverage_db_name";
        case KnownSystemName::LoadCoverageDb: return "$load_coverage_db";
        case KnownSystemName::Clog2: return "$clog2";
        case KnownSystemName::CountBits: return "$countbits";
        case KnownSystemName::CountOnes: return "$countones";
        case KnownSystemName::OneHot: return "$onehot";
        case KnownSystemName::OneHot0: return "$onehot0";
        case KnownSystemName::IsUnknown: return "$isunknown";
        case KnownSystemName::Ln: return "$ln";
        case KnownSystemName::Log10: return "$log10";
        case KnownSystemName::Exp: return "$exp";
        case KnownSystemName::Sqrt: return "$sqrt";
        case KnownSystemName::Floor: return "$floor";
        case KnownSystemName::Ceil: return "$ceil";
        case KnownSystemName::Sin: return "$sin";
        case KnownSystemName::Cos: return "$cos";
        case KnownSystemName::Tan: return "$tan";
        case KnownSystemName::Asin: return "$asin";
        case KnownSystemName::Acos: return "$acos";
        case KnownSystemName::Atan: return "$atan";
        case KnownSystemName::Sinh: return "$sinh";
        case KnownSystemName::Cosh: return "$cosh";
        case KnownSystemName::Tanh: return "$tanh";
        case KnownSystemName::Asinh: return "$asinh";
        case KnownSystemName::Acosh: return "$acosh";
        case KnownSystemName::Atanh: return "$atanh";
        case KnownSystemName::Pow: return "$pow";
        case KnownSystemName::Atan2: return "$atan2";
        case KnownSystemName::Hypot: return "$hypot";
        case KnownSystemName::ValuePlusArgs: return "$value$plusargs";
        case KnownSystemName::GlobalClock: return "$global_clock";
        case KnownSystemName::SFormatF: return "$sformatf";
        case KnownSystemName::PSPrintF: return "$psprintf";
        case KnownSystemName::InferredClock: return "$inferred_clock";
        case KnownSystemName::InferredDisable: return "$inferred_disable";
        case KnownSystemName::Randomize: return "randomize";
        case KnownSystemName::Triggered: return "triggered";
        case KnownSystemName::Matched: return "matched";
        case KnownSystemName::FError: return "$ferror";
        case KnownSystemName::FGets: return "$fgets";
        case KnownSystemName::FScanf: return "$fscanf";
        case KnownSystemName::SScanf: return "$sscanf";
        case KnownSystemName::FRead: return "$fread";
        case KnownSystemName::FOpen: return "$fopen";
        case KnownSystemName::FClose: return "$fclose";
        case KnownSystemName::FGetC: return "$fgetc";
        case KnownSystemName::UngetC: return "$ungetc";
        case KnownSystemName::FTell: return "$ftell";
        case KnownSystemName::FSeek: return "$fseek";
        case KnownSystemName::Rewind: return "$rewind";
        case KnownSystemName::FFlush: return "$fflush";
        case KnownSystemName::FEof: return "$feof";
        case KnownSystemName::Rose: return "$rose";
        case KnownSystemName::Fell: return "$fell";
        case KnownSystemName::Stable: return "$stable";
        case KnownSystemName::Changed: return "$changed";
        case KnownSystemName::PastGclk: return "$past_gclk";
        case KnownSystemName::RoseGclk: return "$rose_gclk";
        case KnownSystemName::FellGclk: return "$fell_gclk";
        case KnownSystemName::StableGclk: return "$stable_gclk";
        case KnownSystemName::ChangedGclk: return "$changed_gclk";
        case KnownSystemName::FutureGclk: return "$future_gclk";
        case KnownSystemName::RisingGclk: return "$rising_gclk";
        case KnownSystemName::FallingGclk: return "$falling_gclk";
        case KnownSystemName::SteadyGclk: return "$steady_gclk";
        case KnownSystemName::ChangingGclk: return "$changing_gclk";
        case KnownSystemName::Sampled: return "$sampled";
        case KnownSystemName::Past: return "$past";
        case KnownSystemName::Stacktrace: return "$stacktrace";
        case KnownSystemName::CountDrivers: return "$countdrivers";
        case KnownSystemName::GetPattern: return "$getpattern";
        case KnownSystemName::TestPlusArgs: return "$test$plusargs";
        case KnownSystemName::Time: return "$time";
        case KnownSystemName::STime: return "$stime";
        case KnownSystemName::RealTime: return "$realtime";
        case KnownSystemName::Random: return "$random";
        case KnownSystemName::URandom: return "$urandom";
        case KnownSystemName::URandomRange: return "$urandom_range";
        case KnownSystemName::ResetCount: return "$reset_count";
        case KnownSystemName::ResetValue: return "$reset_value";
        case KnownSystemName::TimeUnit: return "$timeunit";
        case KnownSystemName::TimePrecision: return "$timeprecision";
        case KnownSystemName::Scale: return "$scale";
        case KnownSystemName::SdfAnnotate: return "$sdf_annotate";
        case KnownSystemName::DistUniform: return "$dist_uniform";
        case KnownSystemName::DistNormal: return "$dist_normal";
        case KnownSystemName::DistExponential: return "$dist_exponential";
        case KnownSystemName::DistPoisson: return "$dist_poisson";
        case KnownSystemName::DistChiSquare: return "$dist_chi_square";
        case KnownSystemName::DistT: return "$dist_t";
        case KnownSystemName::DistErlang: return "$dist_erlang";
        case KnownSystemName::Fatal: return "$fatal";
        case KnownSystemName::StaticAssert: return "$static_assert";
        case KnownSystemName::Cast: return "$cast";
        case KnownSystemName::Info: return "$info";
        case KnownSystemName::Warning: return "$warning";
        case KnownSystemName::Error: return "$error";
        case KnownSystemName::Finish: return "$finish";
        case KnownSystemName::Stop: return "$stop";
        case KnownSystemName::AssertControl: return "$assertcontrol";
        case KnownSystemName::AssertOn: return "$asserton";
        case KnownSystemName::AssertOff: return "$assertoff";
        case KnownSystemName::AssertKill: return "$assertkill";
        case KnownSystemName::AssertPassOn: return "$assertpasson";
        case KnownSystemName::AssertPassOff: return "$assertpassoff";
        case KnownSystemName::AssertFailOn: return "$assertfailon";
        case KnownSystemName::AssertFailOff: return "$assertfailoff";
        case KnownSystemName::AssertNonvacuousOn: return "$assertnonvacuouson";
        case KnownSystemName::AssertVacuousOff: return "$assertvacuousoff";
        case KnownSystemName::Display: return "$display";
        case KnownSystemName::DisplayB: return "$displayb";
        case KnownSystemName::DisplayO: return "$displayo";
        case KnownSystemName::DisplayH: return "$displayh";
        case KnownSystemName::Write: return "$write";
        case KnownSystemName::WriteB: return "$writeb";
        case KnownSystemName::WriteO: return "$writeo";
        case KnownSystemName::WriteH: return "$writeh";
        case KnownSystemName::Strobe: return "$strobe";
        case KnownSystemName::StrobeB: return "$strobeb";
        case KnownSystemName::StrobeO: return "$strobeo";
        case KnownSystemName::StrobeH: return "$strobeh";
        case KnownSystemName::Monitor: return "$monitor";
        case KnownSystemName::MonitorB: return "$monitorb";
        case KnownSystemName::MonitorO: return "$monitoro";
        case KnownSystemName::MonitorH: return "$monitorh";
        case KnownSystemName::FDisplay: return "$fdisplay";
        case KnownSystemName::FDisplayB: return "$fdisplayb";
        case KnownSystemName::FDisplayO: return "$fdisplayo";
        case KnownSystemName::FDisplayH: return "$fdisplayh";
        case KnownSystemName::FWrite: return "$fwrite";
        case KnownSystemName::FWriteB: return "$fwriteb";
        case KnownSystemName::FWriteO: return "$fwriteo";
        case KnownSystemName::FWriteH: return "$fwriteh";
        case KnownSystemName::FStrobe: return "$fstrobe";
        case KnownSystemName::FStrobeB: return "$fstrobeb";
        case KnownSystemName::FStrobeO: return "$fstrobeo";
        case KnownSystemName::FStrobeH: return "$fstrobeh";
        case KnownSystemName::FMonitor: return "$fmonitor";
        case KnownSystemName::FMonitorB: return "$fmonitorb";
        case KnownSystemName::FMonitorO: return "$fmonitoro";
        case KnownSystemName::FMonitorH: return "$fmonitorh";
        case KnownSystemName::SWrite: return "$swrite";
        case KnownSystemName::SWriteB: return "$swriteb";
        case KnownSystemName::SWriteO: return "$swriteo";
        case KnownSystemName::SWriteH: return "$swriteh";
        case KnownSystemName::SFormat: return "$sformat";
        case KnownSystemName::PrintTimeScale: return "$printtimescale";
        case KnownSystemName::DumpVars: return "$dumpvars";
        case KnownSystemName::DumpPorts: return "$dumpports";
        case KnownSystemName::ShowVars: return "$showvars";
        case KnownSystemName::ReadMemB: return "$readmemb";
        case KnownSystemName::ReadMemH: return "$readmemh";
        case KnownSystemName::WriteMemB: return "$writememb";
        case KnownSystemName::WriteMemH: return "$writememh";
        case KnownSystemName::SReadMemB: return "$sreadmemb";
        case KnownSystemName::SReadMemH: return "$sreadmemh";
        case KnownSystemName::System: return "$system";
        case KnownSystemName::List: return "$list";
        case KnownSystemName::Scope: return "$scope";
        case KnownSystemName::Exit: return "$exit";
        case KnownSystemName::TimeFormat: return "$timeformat";
        case KnownSystemName::MonitorOn: return "$monitoron";
        case KnownSystemName::MonitorOff: return "$monitoroff";
        case KnownSystemName::DumpFile: return "$dumpfile";
        case KnownSystemName::DumpOn: return "$dumpon";
        case KnownSystemName::DumpOff: return "$dumpoff";
        case KnownSystemName::DumpAll: return "$dumpall";
        case KnownSystemName::DumpLimit: return "$dumplimit";
        case KnownSystemName::DumpFlush: return "$dumpflush";
        case KnownSystemName::DumpPortsOn: return "$dumpportson";
        case KnownSystemName::DumpPortsOff: return "$dumpportsoff";
        case KnownSystemName::DumpPortsAll: return "$dumpportsall";
        case KnownSystemName::DumpPortsLimit: return "$dumpportslimit";
        case KnownSystemName::DumpPortsFlush: return "$dumpportsflush";
        case KnownSystemName::Input: return "$input";
        case KnownSystemName::Key: return "$key";
        case KnownSystemName::NoKey: return "$nokey";
        case KnownSystemName::Log: return "$log";
        case KnownSystemName::NoLog: return "$nolog";
        case KnownSystemName::Reset: return "$reset";
        case KnownSystemName::Save: return "$save";
        case KnownSystemName::Restart: return "$restart";
        case KnownSystemName::IncSave: return "$incsave";
        case KnownSystemName::ShowScopes: return "$showscopes";
        case KnownSystemName::QInitialize: return "$q_initialize";
        case KnownSystemName::QAdd: return "$q_add";
        case KnownSystemName::QRemove: return "$q_remove";
        case KnownSystemName::QExam: return "$q_exam";
        case KnownSystemName::QFull: return "$q_full";
        case KnownSystemName::AsyncAndArray: return "$async$and$array";
        case KnownSystemName::SyncAndArray: return "$sync$and$array";
        case KnownSystemName::AsyncAndPlane: return "$async$and$plane";
        case KnownSystemName::SyncAndPlane: return "$sync$and$plane";
        case KnownSystemName::AsyncNandArray: return "$async$nand$array";
        case KnownSystemName::SyncNandArray: return "$sync$nand$array";
        case KnownSystemName::AsyncNandPlane: return "$async$nand$plane";
        case KnownSystemName::SyncNandPlane: return "$sync$nand$plane";
        case KnownSystemName::AsyncOrArray: return "$async$or$array";
        case KnownSystemName::SyncOrArray: return "$sync$or$array";
        case KnownSystemName::AsyncOrPlane: return "$async$or$plane";
        case KnownSystemName::SyncOrPlane: return "$sync$or$plane";
        case KnownSystemName::AsyncNorArray: return "$async$nor$array";
        case KnownSystemName::SyncNorArray: return "$sync$nor$array";
        case KnownSystemName::AsyncNorPlane: return "$async$nor$plane";
        case KnownSystemName::SyncNorPlane: return "$sync$nor$plane";
        case KnownSystemName::Reverse: return "reverse";
        case KnownSystemName::Delete: return "delete";
        case KnownSystemName::Exists: return "exists";
        case KnownSystemName::Insert: return "insert";
        case KnownSystemName::Index: return "index";
        case KnownSystemName::Map: return "map";
        case KnownSystemName::ArraySize: return "size";
        case KnownSystemName::Or: return "or";
        case KnownSystemName::And: return "and";
        case KnownSystemName::XOr: return "xor";
        case KnownSystemName::Sum: return "sum";
        case KnownSystemName::Product: return "product";
        case KnownSystemName::Find: return "find";
        case KnownSystemName::FindIndex: return "find_index";
        case KnownSystemName::FindFirst: return "find_first";
        case KnownSystemName::FindFirstIndex: return "find_first_index";
        case KnownSystemName::FindLast: return "find_last";
        case KnownSystemName::FindLastIndex: return "find_last_index";
        case KnownSystemName::Min: return "min";
        case KnownSystemName::Max: return "max";
        case KnownSystemName::Unique: return "unique";
        case KnownSystemName::UniqueIndex: return "unique_index";
        case KnownSystemName::Sort: return "sort";
        case KnownSystemName::Rsort: return "rsort";
        case KnownSystemName::Shuffle: return "shuffle";
        case KnownSystemName::Num: return "num";
        case KnownSystemName::First: return "first";
        case KnownSystemName::Last: return "last";
        case KnownSystemName::Next: return "next";
        case KnownSystemName::Prev: return "prev";
        case KnownSystemName::PopFront: return "pop_front";
        case KnownSystemName::PopBack: return "pop_back";
        case KnownSystemName::PushFront: return "push_front";
        case KnownSystemName::PushBack: return "push_back";
        case KnownSystemName::Name: return "name";
        case KnownSystemName::Len: return "len";
        case KnownSystemName::Putc: return "putc";
        case KnownSystemName::Getc: return "getc";
        case KnownSystemName::Substr: return "substr";
        case KnownSystemName::ToUpper: return "toupper";
        case KnownSystemName::ToLower: return "tolower";
        case KnownSystemName::Compare: return "compare";
        case KnownSystemName::ICompare: return "icompare";
        case KnownSystemName::AToI: return "atoi";
        case KnownSystemName::AToHex: return "atohex";
        case KnownSystemName::AToOct: return "atooct";
        case KnownSystemName::AToBin: return "atobin";
        case KnownSystemName::AToReal: return "atoreal";
        case KnownSystemName::IToA: return "itoa";
        case KnownSystemName::HexToA: return "hextoa";
        case KnownSystemName::OctToA: return "octtoa";
        case KnownSystemName::BinToA: return "bintoa";
        case KnownSystemName::RealToA: return "realtoa";
        case KnownSystemName::RandMode: return "rand_mode";
        case KnownSystemName::ConstraintMode: return "constraint_mode";
    }
    return "";
}

const static flat_hash_map<std::string_view, KnownSystemName> ksnTable = {
    { "$bits", KnownSystemName::Bits },
    { "$typename", KnownSystemName::Typename },
    { "$isunbounded", KnownSystemName::IsUnbounded },
    { "$low", KnownSystemName::Low },
    { "$high", KnownSystemName::High },
    { "$left", KnownSystemName::Left },
    { "$right", KnownSystemName::Right },
    { "$size", KnownSystemName::Size },
    { "$increment", KnownSystemName::Increment },
    { "$dimensions", KnownSystemName::Dimensions },
    { "$unpacked_dimensions", KnownSystemName::UnpackedDimensions },
    { "$rtoi", KnownSystemName::Rtoi },
    { "$itor", KnownSystemName::Itor },
    { "$realtobits", KnownSystemName::RealToBits },
    { "$bitstoreal", KnownSystemName::BitsToReal },
    { "$shortrealtobits", KnownSystemName::ShortrealToBits },
    { "$bitstoshortreal", KnownSystemName::BitsToShortreal },
    { "$signed", KnownSystemName::Signed },
    { "$unsigned", KnownSystemName::Unsigned },
    { "$coverage_control", KnownSystemName::CoverageControl },
    { "$coverage_get_max", KnownSystemName::CoverageGetMax },
    { "$coverage_get", KnownSystemName::CoverageGet },
    { "$coverage_merge", KnownSystemName::CoverageMerge },
    { "$coverage_save", KnownSystemName::CoverageSave },
    { "$get_coverage", KnownSystemName::GetCoverage },
    { "$set_coverage_db_name", KnownSystemName::SetCoverageDbName },
    { "$load_coverage_db", KnownSystemName::LoadCoverageDb },
    { "$clog2", KnownSystemName::Clog2 },
    { "$countbits", KnownSystemName::CountBits },
    { "$countones", KnownSystemName::CountOnes },
    { "$onehot", KnownSystemName::OneHot },
    { "$onehot0", KnownSystemName::OneHot0 },
    { "$isunknown", KnownSystemName::IsUnknown },
    { "$ln", KnownSystemName::Ln },
    { "$log10", KnownSystemName::Log10 },
    { "$exp", KnownSystemName::Exp },
    { "$sqrt", KnownSystemName::Sqrt },
    { "$floor", KnownSystemName::Floor },
    { "$ceil", KnownSystemName::Ceil },
    { "$sin", KnownSystemName::Sin },
    { "$cos", KnownSystemName::Cos },
    { "$tan", KnownSystemName::Tan },
    { "$asin", KnownSystemName::Asin },
    { "$acos", KnownSystemName::Acos },
    { "$atan", KnownSystemName::Atan },
    { "$sinh", KnownSystemName::Sinh },
    { "$cosh", KnownSystemName::Cosh },
    { "$tanh", KnownSystemName::Tanh },
    { "$asinh", KnownSystemName::Asinh },
    { "$acosh", KnownSystemName::Acosh },
    { "$atanh", KnownSystemName::Atanh },
    { "$pow", KnownSystemName::Pow },
    { "$atan2", KnownSystemName::Atan2 },
    { "$hypot", KnownSystemName::Hypot },
    { "$value$plusargs", KnownSystemName::ValuePlusArgs },
    { "$global_clock", KnownSystemName::GlobalClock },
    { "$sformatf", KnownSystemName::SFormatF },
    { "$psprintf", KnownSystemName::PSPrintF },
    { "$inferred_clock", KnownSystemName::InferredClock },
    { "$inferred_disable", KnownSystemName::InferredDisable },
    { "randomize", KnownSystemName::Randomize },
    { "triggered", KnownSystemName::Triggered },
    { "matched", KnownSystemName::Matched },
    { "$ferror", KnownSystemName::FError },
    { "$fgets", KnownSystemName::FGets },
    { "$fscanf", KnownSystemName::FScanf },
    { "$sscanf", KnownSystemName::SScanf },
    { "$fread", KnownSystemName::FRead },
    { "$fopen", KnownSystemName::FOpen },
    { "$fclose", KnownSystemName::FClose },
    { "$fgetc", KnownSystemName::FGetC },
    { "$ungetc", KnownSystemName::UngetC },
    { "$ftell", KnownSystemName::FTell },
    { "$fseek", KnownSystemName::FSeek },
    { "$rewind", KnownSystemName::Rewind },
    { "$fflush", KnownSystemName::FFlush },
    { "$feof", KnownSystemName::FEof },
    { "$rose", KnownSystemName::Rose },
    { "$fell", KnownSystemName::Fell },
    { "$stable", KnownSystemName::Stable },
    { "$changed", KnownSystemName::Changed },
    { "$past_gclk", KnownSystemName::PastGclk },
    { "$rose_gclk", KnownSystemName::RoseGclk },
    { "$fell_gclk", KnownSystemName::FellGclk },
    { "$stable_gclk", KnownSystemName::StableGclk },
    { "$changed_gclk", KnownSystemName::ChangedGclk },
    { "$future_gclk", KnownSystemName::FutureGclk },
    { "$rising_gclk", KnownSystemName::RisingGclk },
    { "$falling_gclk", KnownSystemName::FallingGclk },
    { "$steady_gclk", KnownSystemName::SteadyGclk },
    { "$changing_gclk", KnownSystemName::ChangingGclk },
    { "$sampled", KnownSystemName::Sampled },
    { "$past", KnownSystemName::Past },
    { "$stacktrace", KnownSystemName::Stacktrace },
    { "$countdrivers", KnownSystemName::CountDrivers },
    { "$getpattern", KnownSystemName::GetPattern },
    { "$test$plusargs", KnownSystemName::TestPlusArgs },
    { "$time", KnownSystemName::Time },
    { "$stime", KnownSystemName::STime },
    { "$realtime", KnownSystemName::RealTime },
    { "$random", KnownSystemName::Random },
    { "$urandom", KnownSystemName::URandom },
    { "$urandom_range", KnownSystemName::URandomRange },
    { "$reset_count", KnownSystemName::ResetCount },
    { "$reset_value", KnownSystemName::ResetValue },
    { "$timeunit", KnownSystemName::TimeUnit },
    { "$timeprecision", KnownSystemName::TimePrecision },
    { "$scale", KnownSystemName::Scale },
    { "$sdf_annotate", KnownSystemName::SdfAnnotate },
    { "$dist_uniform", KnownSystemName::DistUniform },
    { "$dist_normal", KnownSystemName::DistNormal },
    { "$dist_exponential", KnownSystemName::DistExponential },
    { "$dist_poisson", KnownSystemName::DistPoisson },
    { "$dist_chi_square", KnownSystemName::DistChiSquare },
    { "$dist_t", KnownSystemName::DistT },
    { "$dist_erlang", KnownSystemName::DistErlang },
    { "$fatal", KnownSystemName::Fatal },
    { "$static_assert", KnownSystemName::StaticAssert },
    { "$cast", KnownSystemName::Cast },
    { "$info", KnownSystemName::Info },
    { "$warning", KnownSystemName::Warning },
    { "$error", KnownSystemName::Error },
    { "$finish", KnownSystemName::Finish },
    { "$stop", KnownSystemName::Stop },
    { "$assertcontrol", KnownSystemName::AssertControl },
    { "$asserton", KnownSystemName::AssertOn },
    { "$assertoff", KnownSystemName::AssertOff },
    { "$assertkill", KnownSystemName::AssertKill },
    { "$assertpasson", KnownSystemName::AssertPassOn },
    { "$assertpassoff", KnownSystemName::AssertPassOff },
    { "$assertfailon", KnownSystemName::AssertFailOn },
    { "$assertfailoff", KnownSystemName::AssertFailOff },
    { "$assertnonvacuouson", KnownSystemName::AssertNonvacuousOn },
    { "$assertvacuousoff", KnownSystemName::AssertVacuousOff },
    { "$display", KnownSystemName::Display },
    { "$displayb", KnownSystemName::DisplayB },
    { "$displayo", KnownSystemName::DisplayO },
    { "$displayh", KnownSystemName::DisplayH },
    { "$write", KnownSystemName::Write },
    { "$writeb", KnownSystemName::WriteB },
    { "$writeo", KnownSystemName::WriteO },
    { "$writeh", KnownSystemName::WriteH },
    { "$strobe", KnownSystemName::Strobe },
    { "$strobeb", KnownSystemName::StrobeB },
    { "$strobeo", KnownSystemName::StrobeO },
    { "$strobeh", KnownSystemName::StrobeH },
    { "$monitor", KnownSystemName::Monitor },
    { "$monitorb", KnownSystemName::MonitorB },
    { "$monitoro", KnownSystemName::MonitorO },
    { "$monitorh", KnownSystemName::MonitorH },
    { "$fdisplay", KnownSystemName::FDisplay },
    { "$fdisplayb", KnownSystemName::FDisplayB },
    { "$fdisplayo", KnownSystemName::FDisplayO },
    { "$fdisplayh", KnownSystemName::FDisplayH },
    { "$fwrite", KnownSystemName::FWrite },
    { "$fwriteb", KnownSystemName::FWriteB },
    { "$fwriteo", KnownSystemName::FWriteO },
    { "$fwriteh", KnownSystemName::FWriteH },
    { "$fstrobe", KnownSystemName::FStrobe },
    { "$fstrobeb", KnownSystemName::FStrobeB },
    { "$fstrobeo", KnownSystemName::FStrobeO },
    { "$fstrobeh", KnownSystemName::FStrobeH },
    { "$fmonitor", KnownSystemName::FMonitor },
    { "$fmonitorb", KnownSystemName::FMonitorB },
    { "$fmonitoro", KnownSystemName::FMonitorO },
    { "$fmonitorh", KnownSystemName::FMonitorH },
    { "$swrite", KnownSystemName::SWrite },
    { "$swriteb", KnownSystemName::SWriteB },
    { "$swriteo", KnownSystemName::SWriteO },
    { "$swriteh", KnownSystemName::SWriteH },
    { "$sformat", KnownSystemName::SFormat },
    { "$printtimescale", KnownSystemName::PrintTimeScale },
    { "$dumpvars", KnownSystemName::DumpVars },
    { "$dumpports", KnownSystemName::DumpPorts },
    { "$showvars", KnownSystemName::ShowVars },
    { "$readmemb", KnownSystemName::ReadMemB },
    { "$readmemh", KnownSystemName::ReadMemH },
    { "$writememb", KnownSystemName::WriteMemB },
    { "$writememh", KnownSystemName::WriteMemH },
    { "$sreadmemb", KnownSystemName::SReadMemB },
    { "$sreadmemh", KnownSystemName::SReadMemH },
    { "$system", KnownSystemName::System },
    { "$list", KnownSystemName::List },
    { "$scope", KnownSystemName::Scope },
    { "$exit", KnownSystemName::Exit },
    { "$timeformat", KnownSystemName::TimeFormat },
    { "$monitoron", KnownSystemName::MonitorOn },
    { "$monitoroff", KnownSystemName::MonitorOff },
    { "$dumpfile", KnownSystemName::DumpFile },
    { "$dumpon", KnownSystemName::DumpOn },
    { "$dumpoff", KnownSystemName::DumpOff },
    { "$dumpall", KnownSystemName::DumpAll },
    { "$dumplimit", KnownSystemName::DumpLimit },
    { "$dumpflush", KnownSystemName::DumpFlush },
    { "$dumpportson", KnownSystemName::DumpPortsOn },
    { "$dumpportsoff", KnownSystemName::DumpPortsOff },
    { "$dumpportsall", KnownSystemName::DumpPortsAll },
    { "$dumpportslimit", KnownSystemName::DumpPortsLimit },
    { "$dumpportsflush", KnownSystemName::DumpPortsFlush },
    { "$input", KnownSystemName::Input },
    { "$key", KnownSystemName::Key },
    { "$nokey", KnownSystemName::NoKey },
    { "$log", KnownSystemName::Log },
    { "$nolog", KnownSystemName::NoLog },
    { "$reset", KnownSystemName::Reset },
    { "$save", KnownSystemName::Save },
    { "$restart", KnownSystemName::Restart },
    { "$incsave", KnownSystemName::IncSave },
    { "$showscopes", KnownSystemName::ShowScopes },
    { "$q_initialize", KnownSystemName::QInitialize },
    { "$q_add", KnownSystemName::QAdd },
    { "$q_remove", KnownSystemName::QRemove },
    { "$q_exam", KnownSystemName::QExam },
    { "$q_full", KnownSystemName::QFull },
    { "$async$and$array", KnownSystemName::AsyncAndArray },
    { "$sync$and$array", KnownSystemName::SyncAndArray },
    { "$async$and$plane", KnownSystemName::AsyncAndPlane },
    { "$sync$and$plane", KnownSystemName::SyncAndPlane },
    { "$async$nand$array", KnownSystemName::AsyncNandArray },
    { "$sync$nand$array", KnownSystemName::SyncNandArray },
    { "$async$nand$plane", KnownSystemName::AsyncNandPlane },
    { "$sync$nand$plane", KnownSystemName::SyncNandPlane },
    { "$async$or$array", KnownSystemName::AsyncOrArray },
    { "$sync$or$array", KnownSystemName::SyncOrArray },
    { "$async$or$plane", KnownSystemName::AsyncOrPlane },
    { "$sync$or$plane", KnownSystemName::SyncOrPlane },
    { "$async$nor$array", KnownSystemName::AsyncNorArray },
    { "$sync$nor$array", KnownSystemName::SyncNorArray },
    { "$async$nor$plane", KnownSystemName::AsyncNorPlane },
    { "$sync$nor$plane", KnownSystemName::SyncNorPlane },
    { "reverse", KnownSystemName::Reverse },
    { "delete", KnownSystemName::Delete },
    { "exists", KnownSystemName::Exists },
    { "insert", KnownSystemName::Insert },
    { "index", KnownSystemName::Index },
    { "map", KnownSystemName::Map },
    { "size", KnownSystemName::ArraySize },
    { "or", KnownSystemName::Or },
    { "and", KnownSystemName::And },
    { "xor", KnownSystemName::XOr },
    { "sum", KnownSystemName::Sum },
    { "product", KnownSystemName::Product },
    { "find", KnownSystemName::Find },
    { "find_index", KnownSystemName::FindIndex },
    { "find_first", KnownSystemName::FindFirst },
    { "find_first_index", KnownSystemName::FindFirstIndex },
    { "find_last", KnownSystemName::FindLast },
    { "find_last_index", KnownSystemName::FindLastIndex },
    { "min", KnownSystemName::Min },
    { "max", KnownSystemName::Max },
    { "unique", KnownSystemName::Unique },
    { "unique_index", KnownSystemName::UniqueIndex },
    { "sort", KnownSystemName::Sort },
    { "rsort", KnownSystemName::Rsort },
    { "shuffle", KnownSystemName::Shuffle },
    { "num", KnownSystemName::Num },
    { "first", KnownSystemName::First },
    { "last", KnownSystemName::Last },
    { "next", KnownSystemName::Next },
    { "prev", KnownSystemName::Prev },
    { "pop_front", KnownSystemName::PopFront },
    { "pop_back", KnownSystemName::PopBack },
    { "push_front", KnownSystemName::PushFront },
    { "push_back", KnownSystemName::PushBack },
    { "name", KnownSystemName::Name },
    { "len", KnownSystemName::Len },
    { "putc", KnownSystemName::Putc },
    { "getc", KnownSystemName::Getc },
    { "substr", KnownSystemName::Substr },
    { "toupper", KnownSystemName::ToUpper },
    { "tolower", KnownSystemName::ToLower },
    { "compare", KnownSystemName::Compare },
    { "icompare", KnownSystemName::ICompare },
    { "atoi", KnownSystemName::AToI },
    { "atohex", KnownSystemName::AToHex },
    { "atooct", KnownSystemName::AToOct },
    { "atobin", KnownSystemName::AToBin },
    { "atoreal", KnownSystemName::AToReal },
    { "itoa", KnownSystemName::IToA },
    { "hextoa", KnownSystemName::HexToA },
    { "octtoa", KnownSystemName::OctToA },
    { "bintoa", KnownSystemName::BinToA },
    { "realtoa", KnownSystemName::RealToA },
    { "rand_mode", KnownSystemName::RandMode },
    { "constraint_mode", KnownSystemName::ConstraintMode },
};

KnownSystemName parseKnownSystemName(std::string_view str) {
    if (auto it = ksnTable.find(str); it != ksnTable.end())
        return it->second;
    return KnownSystemName::Unknown;
}

decltype(KnownSystemName_traits::values) KnownSystemName_traits::values = {
    KnownSystemName::Unknown,
    KnownSystemName::Bits,
    KnownSystemName::Typename,
    KnownSystemName::IsUnbounded,
    KnownSystemName::Low,
    KnownSystemName::High,
    KnownSystemName::Left,
    KnownSystemName::Right,
    KnownSystemName::Size,
    KnownSystemName::Increment,
    KnownSystemName::Dimensions,
    KnownSystemName::UnpackedDimensions,
    KnownSystemName::Rtoi,
    KnownSystemName::Itor,
    KnownSystemName::RealToBits,
    KnownSystemName::BitsToReal,
    KnownSystemName::ShortrealToBits,
    KnownSystemName::BitsToShortreal,
    KnownSystemName::Signed,
    KnownSystemName::Unsigned,
    KnownSystemName::CoverageControl,
    KnownSystemName::CoverageGetMax,
    KnownSystemName::CoverageGet,
    KnownSystemName::CoverageMerge,
    KnownSystemName::CoverageSave,
    KnownSystemName::GetCoverage,
    KnownSystemName::SetCoverageDbName,
    KnownSystemName::LoadCoverageDb,
    KnownSystemName::Clog2,
    KnownSystemName::CountBits,
    KnownSystemName::CountOnes,
    KnownSystemName::OneHot,
    KnownSystemName::OneHot0,
    KnownSystemName::IsUnknown,
    KnownSystemName::Ln,
    KnownSystemName::Log10,
    KnownSystemName::Exp,
    KnownSystemName::Sqrt,
    KnownSystemName::Floor,
    KnownSystemName::Ceil,
    KnownSystemName::Sin,
    KnownSystemName::Cos,
    KnownSystemName::Tan,
    KnownSystemName::Asin,
    KnownSystemName::Acos,
    KnownSystemName::Atan,
    KnownSystemName::Sinh,
    KnownSystemName::Cosh,
    KnownSystemName::Tanh,
    KnownSystemName::Asinh,
    KnownSystemName::Acosh,
    KnownSystemName::Atanh,
    KnownSystemName::Pow,
    KnownSystemName::Atan2,
    KnownSystemName::Hypot,
    KnownSystemName::ValuePlusArgs,
    KnownSystemName::GlobalClock,
    KnownSystemName::SFormatF,
    KnownSystemName::PSPrintF,
    KnownSystemName::InferredClock,
    KnownSystemName::InferredDisable,
    KnownSystemName::Randomize,
    KnownSystemName::Triggered,
    KnownSystemName::Matched,
    KnownSystemName::FError,
    KnownSystemName::FGets,
    KnownSystemName::FScanf,
    KnownSystemName::SScanf,
    KnownSystemName::FRead,
    KnownSystemName::FOpen,
    KnownSystemName::FClose,
    KnownSystemName::FGetC,
    KnownSystemName::UngetC,
    KnownSystemName::FTell,
    KnownSystemName::FSeek,
    KnownSystemName::Rewind,
    KnownSystemName::FFlush,
    KnownSystemName::FEof,
    KnownSystemName::Rose,
    KnownSystemName::Fell,
    KnownSystemName::Stable,
    KnownSystemName::Changed,
    KnownSystemName::PastGclk,
    KnownSystemName::RoseGclk,
    KnownSystemName::FellGclk,
    KnownSystemName::StableGclk,
    KnownSystemName::ChangedGclk,
    KnownSystemName::FutureGclk,
    KnownSystemName::RisingGclk,
    KnownSystemName::FallingGclk,
    KnownSystemName::SteadyGclk,
    KnownSystemName::ChangingGclk,
    KnownSystemName::Sampled,
    KnownSystemName::Past,
    KnownSystemName::Stacktrace,
    KnownSystemName::CountDrivers,
    KnownSystemName::GetPattern,
    KnownSystemName::TestPlusArgs,
    KnownSystemName::Time,
    KnownSystemName::STime,
    KnownSystemName::RealTime,
    KnownSystemName::Random,
    KnownSystemName::URandom,
    KnownSystemName::URandomRange,
    KnownSystemName::ResetCount,
    KnownSystemName::ResetValue,
    KnownSystemName::TimeUnit,
    KnownSystemName::TimePrecision,
    KnownSystemName::Scale,
    KnownSystemName::SdfAnnotate,
    KnownSystemName::DistUniform,
    KnownSystemName::DistNormal,
    KnownSystemName::DistExponential,
    KnownSystemName::DistPoisson,
    KnownSystemName::DistChiSquare,
    KnownSystemName::DistT,
    KnownSystemName::DistErlang,
    KnownSystemName::Fatal,
    KnownSystemName::StaticAssert,
    KnownSystemName::Cast,
    KnownSystemName::Info,
    KnownSystemName::Warning,
    KnownSystemName::Error,
    KnownSystemName::Finish,
    KnownSystemName::Stop,
    KnownSystemName::AssertControl,
    KnownSystemName::AssertOn,
    KnownSystemName::AssertOff,
    KnownSystemName::AssertKill,
    KnownSystemName::AssertPassOn,
    KnownSystemName::AssertPassOff,
    KnownSystemName::AssertFailOn,
    KnownSystemName::AssertFailOff,
    KnownSystemName::AssertNonvacuousOn,
    KnownSystemName::AssertVacuousOff,
    KnownSystemName::Display,
    KnownSystemName::DisplayB,
    KnownSystemName::DisplayO,
    KnownSystemName::DisplayH,
    KnownSystemName::Write,
    KnownSystemName::WriteB,
    KnownSystemName::WriteO,
    KnownSystemName::WriteH,
    KnownSystemName::Strobe,
    KnownSystemName::StrobeB,
    KnownSystemName::StrobeO,
    KnownSystemName::StrobeH,
    KnownSystemName::Monitor,
    KnownSystemName::MonitorB,
    KnownSystemName::MonitorO,
    KnownSystemName::MonitorH,
    KnownSystemName::FDisplay,
    KnownSystemName::FDisplayB,
    KnownSystemName::FDisplayO,
    KnownSystemName::FDisplayH,
    KnownSystemName::FWrite,
    KnownSystemName::FWriteB,
    KnownSystemName::FWriteO,
    KnownSystemName::FWriteH,
    KnownSystemName::FStrobe,
    KnownSystemName::FStrobeB,
    KnownSystemName::FStrobeO,
    KnownSystemName::FStrobeH,
    KnownSystemName::FMonitor,
    KnownSystemName::FMonitorB,
    KnownSystemName::FMonitorO,
    KnownSystemName::FMonitorH,
    KnownSystemName::SWrite,
    KnownSystemName::SWriteB,
    KnownSystemName::SWriteO,
    KnownSystemName::SWriteH,
    KnownSystemName::SFormat,
    KnownSystemName::PrintTimeScale,
    KnownSystemName::DumpVars,
    KnownSystemName::DumpPorts,
    KnownSystemName::ShowVars,
    KnownSystemName::ReadMemB,
    KnownSystemName::ReadMemH,
    KnownSystemName::WriteMemB,
    KnownSystemName::WriteMemH,
    KnownSystemName::SReadMemB,
    KnownSystemName::SReadMemH,
    KnownSystemName::System,
    KnownSystemName::List,
    KnownSystemName::Scope,
    KnownSystemName::Exit,
    KnownSystemName::TimeFormat,
    KnownSystemName::MonitorOn,
    KnownSystemName::MonitorOff,
    KnownSystemName::DumpFile,
    KnownSystemName::DumpOn,
    KnownSystemName::DumpOff,
    KnownSystemName::DumpAll,
    KnownSystemName::DumpLimit,
    KnownSystemName::DumpFlush,
    KnownSystemName::DumpPortsOn,
    KnownSystemName::DumpPortsOff,
    KnownSystemName::DumpPortsAll,
    KnownSystemName::DumpPortsLimit,
    KnownSystemName::DumpPortsFlush,
    KnownSystemName::Input,
    KnownSystemName::Key,
    KnownSystemName::NoKey,
    KnownSystemName::Log,
    KnownSystemName::NoLog,
    KnownSystemName::Reset,
    KnownSystemName::Save,
    KnownSystemName::Restart,
    KnownSystemName::IncSave,
    KnownSystemName::ShowScopes,
    KnownSystemName::QInitialize,
    KnownSystemName::QAdd,
    KnownSystemName::QRemove,
    KnownSystemName::QExam,
    KnownSystemName::QFull,
    KnownSystemName::AsyncAndArray,
    KnownSystemName::SyncAndArray,
    KnownSystemName::AsyncAndPlane,
    KnownSystemName::SyncAndPlane,
    KnownSystemName::AsyncNandArray,
    KnownSystemName::SyncNandArray,
    KnownSystemName::AsyncNandPlane,
    KnownSystemName::SyncNandPlane,
    KnownSystemName::AsyncOrArray,
    KnownSystemName::SyncOrArray,
    KnownSystemName::AsyncOrPlane,
    KnownSystemName::SyncOrPlane,
    KnownSystemName::AsyncNorArray,
    KnownSystemName::SyncNorArray,
    KnownSystemName::AsyncNorPlane,
    KnownSystemName::SyncNorPlane,
    KnownSystemName::Reverse,
    KnownSystemName::Delete,
    KnownSystemName::Exists,
    KnownSystemName::Insert,
    KnownSystemName::Index,
    KnownSystemName::Map,
    KnownSystemName::ArraySize,
    KnownSystemName::Or,
    KnownSystemName::And,
    KnownSystemName::XOr,
    KnownSystemName::Sum,
    KnownSystemName::Product,
    KnownSystemName::Find,
    KnownSystemName::FindIndex,
    KnownSystemName::FindFirst,
    KnownSystemName::FindFirstIndex,
    KnownSystemName::FindLast,
    KnownSystemName::FindLastIndex,
    KnownSystemName::Min,
    KnownSystemName::Max,
    KnownSystemName::Unique,
    KnownSystemName::UniqueIndex,
    KnownSystemName::Sort,
    KnownSystemName::Rsort,
    KnownSystemName::Shuffle,
    KnownSystemName::Num,
    KnownSystemName::First,
    KnownSystemName::Last,
    KnownSystemName::Next,
    KnownSystemName::Prev,
    KnownSystemName::PopFront,
    KnownSystemName::PopBack,
    KnownSystemName::PushFront,
    KnownSystemName::PushBack,
    KnownSystemName::Name,
    KnownSystemName::Len,
    KnownSystemName::Putc,
    KnownSystemName::Getc,
    KnownSystemName::Substr,
    KnownSystemName::ToUpper,
    KnownSystemName::ToLower,
    KnownSystemName::Compare,
    KnownSystemName::ICompare,
    KnownSystemName::AToI,
    KnownSystemName::AToHex,
    KnownSystemName::AToOct,
    KnownSystemName::AToBin,
    KnownSystemName::AToReal,
    KnownSystemName::IToA,
    KnownSystemName::HexToA,
    KnownSystemName::OctToA,
    KnownSystemName::BinToA,
    KnownSystemName::RealToA,
    KnownSystemName::RandMode,
    KnownSystemName::ConstraintMode,
};

}
