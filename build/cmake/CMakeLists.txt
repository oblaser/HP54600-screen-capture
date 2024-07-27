
# author        Oliver Blaser
# date          27.07.2024
# copyright     GPL-3.0 - Copyright (c) 2024 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(hp54600-screen-capture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(SOURCES)



#
# SDK
#

# omw
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../sdk/omw/build/cmake/libomw.a/ ${CMAKE_CURRENT_LIST_DIR}/../../sdk/omw/build/cmake/libomw.a/)
include_directories(../../sdk/omw/include)

# olcPGE
set(SOURCES ${SOURCES} ../../sdk/pge/olcPixelGameEngine.cpp)
include_directories(../../sdk/pge)




#
# the application
#

set(BINNAME hp54600-screen-capture)

if(_DEBUG)
    add_definitions(-D_DEBUG)
endif()

include_directories(../../src/)

set(SOURCES ${SOURCES}
../../src/middleware/util.cpp
../../src/main.cpp
)

add_executable(${BINNAME} ${SOURCES})
target_link_libraries(${BINNAME} omw)

# libraries needed by olcPGE
if(UNIX AND NOT APPLE)
    target_link_libraries(${BINNAME} X11 GL pthread png)
    # sudo apt-get install libx11-dev
    # sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
    # sudo apt-get install libpng-dev
endif()
