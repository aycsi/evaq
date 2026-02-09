cmake_minimum_required(VERSION 3.20)
project(evaq)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine)

add_executable(evaq_main engine/main.cpp)
target_link_libraries(evaq_main engine)
