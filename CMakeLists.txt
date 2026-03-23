cmake_minimum_required(VERSION 3.28)
set(EXECUTABLE project_name)
project(${EXECUTABLE} LANGUAGES CXX)

# ====================================
# Default build settings
# ====================================
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ====================================
# Core library target
# ====================================
add_library(${EXECUTABLE}_core
  ${CMAKE_CURRENT_LIST_DIR}/src/command_runner.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/cli/cli.cpp
)

target_include_directories(${EXECUTABLE}_core
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
    ${CMAKE_CURRENT_LIST_DIR}/inc/cli
)

# ====================================
# Executable target
# ====================================
add_executable(${EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)
target_link_libraries(${EXECUTABLE} PRIVATE ${EXECUTABLE}_core)

# ====================================
# Unit test target
# ====================================
add_executable(unit_tests ${CMAKE_CURRENT_LIST_DIR}/test/test_main.cpp)
target_link_libraries(unit_tests PRIVATE ${EXECUTABLE}_core)

# ====================================
# Enable testing and add unit tests to ctest
# ====================================
enable_testing()
add_test(NAME all_tests COMMAND unit_tests)
