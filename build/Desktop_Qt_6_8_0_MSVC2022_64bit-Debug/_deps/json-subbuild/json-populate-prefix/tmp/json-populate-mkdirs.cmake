# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-src"
  "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-build"
  "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-subbuild/json-populate-prefix"
  "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-subbuild/json-populate-prefix/tmp"
  "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
  "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-subbuild/json-populate-prefix/src"
  "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/cpp_projects/where/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
