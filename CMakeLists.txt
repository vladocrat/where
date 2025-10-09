cmake_minimum_required(VERSION 3.16)

project(where VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTORCC ON)

set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/resources)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Svg)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(src/core)
add_subdirectory(src/frontend)
include(3rd_party/LoadDependancies.cmake)

file(GLOB SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB HEADERS CONFIGURE_DEPENDS *.hpp)
file(GLOB ICONS CONFIGURE_DEPENDS ${RESOURCES_PATH}/icons/*.svg)

qt_add_executable(where
    main.cpp
    ${RESOURCES_PATH}/resources.qrc
    ${HEADERS}
    ${SOURCES}
)

qt_add_qml_module(where
    URI where
    VERSION 1.0
    QML_FILES
        Main.qml
        Searchbar.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(where PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appwhere
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(where
    PRIVATE
    Qt6::Quick
    Qt6::Svg
    core
    frontend
    nlohmann_json::nlohmann_json
)

include(GNUInstallDirs)
install(TARGETS where
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
