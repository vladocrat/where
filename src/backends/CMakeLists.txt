file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS *.hpp)
file(COPY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/backends.json ${CMAKE_BINARY_DIR}/backends.json)

add_library(backends 
   ${HEADERS}
   ${SOURCES}
)

target_link_libraries(backends nlohmann_json::nlohmann_json)
