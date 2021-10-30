#CMakeLists.txt
cmake_minimum_required (VERSION 3.6)
project(maidea)

add_executable(maidea src/main.cpp)

add_subdirectory(sleepy-discord)
target_link_libraries(maidea sleepy-discord)



