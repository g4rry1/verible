# ~~~
# SPDX-FileCopyrightText: Michael Popoloski
# SPDX-License-Identifier: MIT
# ~~~

# Internal file used to force a reconfiguration if the git commit changes.
set(HEAD_HASH)

file(READ "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/git-data/HEAD" HEAD_CONTENTS LIMIT 1024)

string(STRIP "${HEAD_CONTENTS}" HEAD_CONTENTS)
if(HEAD_CONTENTS MATCHES "ref")
  # named branch
  string(REPLACE "ref: " "" HEAD_REF "${HEAD_CONTENTS}")
  if(EXISTS "/home/dmitrii/visetog/verible/third_party/slang/.git/${HEAD_REF}")
    configure_file("/home/dmitrii/visetog/verible/third_party/slang/.git/${HEAD_REF}" "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/git-data/head-ref" COPYONLY)
  else()
    configure_file("/home/dmitrii/visetog/verible/third_party/slang/.git/packed-refs" "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/git-data/packed-refs" COPYONLY)
    file(READ "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/git-data/packed-refs" PACKED_REFS)
    if(${PACKED_REFS} MATCHES "([0-9a-z]*) ${HEAD_REF}")
      set(HEAD_HASH "${CMAKE_MATCH_1}")
    endif()
  endif()
else()
  # detached HEAD
  configure_file("/home/dmitrii/visetog/verible/third_party/slang/.git/HEAD" "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/git-data/head-ref" COPYONLY)
endif()

if(NOT HEAD_HASH)
  file(READ "/home/dmitrii/visetog/verible/third_party/slang/build-system/CMakeFiles/git-data/head-ref" HEAD_HASH LIMIT 1024)
  string(STRIP "${HEAD_HASH}" HEAD_HASH)
endif()
