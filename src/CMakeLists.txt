#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(myproject)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wall -Wextra -Wno-unused -pedantic")

set(LIB_NAME "SharedCode")
add_library(${LIB_NAME}
    engine/spriteentity.cpp
    engine/sprite.cpp
    engine/world.cpp
    engine/entity.cpp
    engine/mouseeventhandler.cpp
    engine/entitygroup.cpp
    engine/physicsentity.cpp
    engine/zui/uicomponent.cpp
    engine/zui/window.cpp
    engine/zui/inputcomponent.cpp
    engine/zui/button.cpp
    engine/zui/textbutton.cpp
    engine/zui/imglistelement.cpp
    engine/zui/imglist.cpp
    engine/line.cpp
    engine/vec2f.cpp
    engine/platform.cpp
    engine/ground.cpp
    engine/humanentity.cpp
    player.cpp
    civilian.cpp
    soldier.cpp
    hidingspot.cpp
    hidingspottemplate.cpp
    bloodsplatter.cpp
)

# Define sources and executable
set(EXECUTABLE_NAME "myproject")
add_executable(${EXECUTABLE_NAME} 
    #Include for directory support on windows
    #depend/dirent.h
    main.cpp 
    game.cpp
    )
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(${EXECUTABLE_NAME} ${LIB_NAME})
# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)
