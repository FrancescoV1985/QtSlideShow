
cmake_minimum_required(VERSION 3.16)
project(slideshow_viewer LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR ".")
endif()


set(CMAKE_AUTOMOC ON)

find_package(Qt6
    REQUIRED COMPONENTS Core Gui Widgets Concurrent
)


set(SRC_DIR "src")
set(INCLUDE_DIR "include")

add_executable(slideshow_viewer
    ${SRC_DIR}/slideShowViewer.cpp
    ${SRC_DIR}/slideShowDelegate.cpp
    ${SRC_DIR}/slideShowView.cpp
    ${SRC_DIR}/slideShowWorker.cpp
    ${INCLUDE_DIR}/commonDef.h
    ${INCLUDE_DIR}/slideShowViewer.h
    ${INCLUDE_DIR}/slideShowDelegate.h
    ${INCLUDE_DIR}/slideShowView.h
    ${INCLUDE_DIR}/slideShowWorker.h

    main.cpp
)

target_include_directories(slideshow_viewer PRIVATE

$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/>
)


set_target_properties(slideshow_viewer PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(slideshow_viewer PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Concurrent

)


install(TARGETS slideshow_viewer
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
