file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS *.hpp)

add_library(core 
   ${HEADERS}
   ${SOURCES}
)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

set_target_properties(core PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src"
)

target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json Qt6::Core)
