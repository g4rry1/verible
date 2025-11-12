# Install script for directory: /home/dmitrii/visetog/verible/third_party/slang

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/dmitrii/visetog/verible/third_party/slang/build-system/_deps/fmt-build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ieee1800" TYPE DIRECTORY FILES "/home/dmitrii/visetog/verible/third_party/slang/external/ieee1800/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/home/dmitrii/visetog/verible/third_party/slang/external/expected.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/lib/libfmt.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/args.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/base.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/chrono.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/color.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/compile.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/core.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/format.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/format-inl.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/os.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/ostream.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/printf.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/ranges.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/std.h"
    "/home/dmitrii/visetog/verible/third_party/slang/include/fmt/xchar.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/_deps/fmt-src/include/fmt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/dmitrii/visetog/verible/third_party/slang/external/boost_unordered.hpp"
    "/home/dmitrii/visetog/verible/third_party/slang/external/boost_concurrent.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/lib/libmimalloc.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mimalloc-2.2" TYPE FILE FILES
    "/home/dmitrii/visetog/verible/third_party/slang/build-system/_deps/mimalloc-src/include/mimalloc.h"
    "/home/dmitrii/visetog/verible/third_party/slang/build-system/_deps/mimalloc-src/include/mimalloc-override.h"
    "/home/dmitrii/visetog/verible/third_party/slang/build-system/_deps/mimalloc-src/include/mimalloc-new-delete.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/dmitrii/visetog/verible/third_party/slang/build-system/source/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/dmitrii/visetog/verible/third_party/slang/build-system/tools/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsvlang.so.9.1.150"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsvlang.so.9"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "\$ORIGIN:\$ORIGIN/../lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/dmitrii/visetog/verible/third_party/slang/build-system/lib/libsvlang.so.9.1.150"
    "/home/dmitrii/visetog/verible/third_party/slang/build-system/lib/libsvlang.so.9"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsvlang.so.9.1.150"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsvlang.so.9"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "::::::::::::::::::::::"
           NEW_RPATH "\$ORIGIN:\$ORIGIN/../lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/lib/libsvlang.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/slang" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/slang")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/slang"
         RPATH "\$ORIGIN:\$ORIGIN/../lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/bin/slang")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/slang" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/slang")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/slang"
         OLD_RPATH "/home/dmitrii/visetog/verible/third_party/slang/build-system/lib:"
         NEW_RPATH "\$ORIGIN:\$ORIGIN/../lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/slang")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/slang/slangTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/slang/slangTargets.cmake"
         "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/Export/0d4d3fe6e1345ccb999055d3488ce1cc/slangTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/slang/slangTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/slang/slangTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/slang" TYPE FILE FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/Export/0d4d3fe6e1345ccb999055d3488ce1cc/slangTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/slang" TYPE FILE FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/Export/0d4d3fe6e1345ccb999055d3488ce1cc/slangTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/slang" TYPE FILE FILES
    "/home/dmitrii/visetog/verible/third_party/slang/build-system/slangConfig.cmake"
    "/home/dmitrii/visetog/verible/third_party/slang/build-system/slangConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" TYPE FILE FILES "/home/dmitrii/visetog/verible/third_party/slang/build-system/sv-lang.pc")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/dmitrii/visetog/verible/third_party/slang/build-system/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
