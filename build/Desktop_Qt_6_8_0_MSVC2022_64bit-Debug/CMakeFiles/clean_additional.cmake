# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\where_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\where_autogen.dir\\ParseCache.txt"
  "src\\core\\CMakeFiles\\core_autogen.dir\\AutogenUsed.txt"
  "src\\core\\CMakeFiles\\core_autogen.dir\\ParseCache.txt"
  "src\\core\\core_autogen"
  "src\\frontend\\CMakeFiles\\frontend_autogen.dir\\AutogenUsed.txt"
  "src\\frontend\\CMakeFiles\\frontend_autogen.dir\\ParseCache.txt"
  "src\\frontend\\frontend_autogen"
  "where_autogen"
  )
endif()
