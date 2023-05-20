# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CW_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CW_autogen.dir\\ParseCache.txt"
  "CW_autogen"
  )
endif()
