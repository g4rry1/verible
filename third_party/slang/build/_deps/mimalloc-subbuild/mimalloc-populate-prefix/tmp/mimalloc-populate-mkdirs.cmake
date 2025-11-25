# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-src"
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-build"
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix"
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/tmp"
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp"
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src"
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
