file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS *.hpp)

add_library(frontend 
   ${HEADERS}
   ${SOURCES}
)

target_include_directories(frontend PUBLIC ${CMAKE_SOURCE_DIR}/src)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick)

set_target_properties(frontend PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src"
)

target_link_libraries(frontend Qt6::Core Qt6::Quick core nlohmann_json::nlohmann_json)
