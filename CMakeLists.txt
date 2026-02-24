cmake_minimum_required(VERSION 3.19)

project(turtlepreter
    VERSION     0.0.1
    DESCRIPTION "Interpreter of commands for a turtle"
    LANGUAGES   C CXX
)

set(CMAKE_CXX_STANDARD 20)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/CMakeLists.txt")
    add_subdirectory(lib)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../lib/CMakeLists.txt")
    add_subdirectory(../lib lib)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/CMakeLists.txt")
    add_subdirectory(../../lib lib)
else()
    message(FATAL_ERROR "The 'lib' directory containing dependencies (friimgui, heap) is missing. Please ensure it exists in '${CMAKE_CURRENT_SOURCE_DIR}/lib' or '${CMAKE_CURRENT_SOURCE_DIR}/../lib' or '${CMAKE_CURRENT_SOURCE_DIR}/../../lib'.")
endif()

add_subdirectory(turtlepreter)
