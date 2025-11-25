# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitclone-lastrun.txt" AND EXISTS "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitinfo.txt" AND
  "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitclone-lastrun.txt" IS_NEWER_THAN "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --depth 1 --no-single-branch --config "advice.detachedHead=false" "https://github.com/microsoft/mimalloc.git" "mimalloc-src"
    WORKING_DIRECTORY "/home/dmitrii/visetog/verible/third_party/slang/build/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/microsoft/mimalloc.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "v2.2.4" --
  WORKING_DIRECTORY "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v2.2.4'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitinfo.txt" "/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/dmitrii/visetog/verible/third_party/slang/build/_deps/mimalloc-subbuild/mimalloc-populate-prefix/src/mimalloc-populate-stamp/mimalloc-populate-gitclone-lastrun.txt'")
endif()
