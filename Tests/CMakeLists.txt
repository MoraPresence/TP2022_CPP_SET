cmake_minimum_required(VERSION 3.0)
project(SET_tests CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wconversion -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wunreachable-code -pedantic -pthread")

if (ENABLE_TESTING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage -fPIC")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${RBTREE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${RBTREE_LIBRARIES} GTest::gtest_main)

enable_testing()
add_test(NAME RBTREE_tests COMMAND RBTREE_tests)
