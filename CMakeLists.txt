cmake_minimum_required(VERSION 3.0)
project(SET CXX)

option(ENABLE_TESTING "Build for test" ON)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(RBTree)

add_subdirectory(Set)

add_subdirectory(Tests)
