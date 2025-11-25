# Install script for directory: /home/dmitrii/visetog/verible/third_party/slang/source

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dmitrii/visetog/verible/third_party/slang/install")
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
  include("/home/dmitrii/visetog/verible/third_party/slang/build/source/ast/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/dmitrii/visetog/verible/third_party/slang/source/../include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/slang/diagnostics" TYPE DIRECTORY FILES "/home/dmitrii/visetog/verible/third_party/slang/build/source/slang/diagnostics/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/slang/syntax" TYPE FILE FILES
    "/home/dmitrii/visetog/verible/third_party/slang/build/source/slang/syntax/AllSyntax.h"
    "/home/dmitrii/visetog/verible/third_party/slang/build/source/slang/syntax/SyntaxKind.h"
    "/home/dmitrii/visetog/verible/third_party/slang/build/source/slang/syntax/SyntaxFwd.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/slang/parsing" TYPE FILE FILES
    "/home/dmitrii/visetog/verible/third_party/slang/build/source/slang/parsing/TokenKind.h"
    "/home/dmitrii/visetog/verible/third_party/slang/build/source/slang/parsing/KnownSystemName.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "slang_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/slang" TYPE FILE FILES "/home/dmitrii/visetog/verible/third_party/slang/build/source/slang/slang_export.h")
endif()

