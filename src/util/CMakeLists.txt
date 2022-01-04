add_library(Util INTERFACE)

add_subdirectory(config)

add_library(ConsoleOut ConsoleOut.cpp)

target_link_libraries(Util INTERFACE ConsoleOut)
target_link_libraries(Util INTERFACE Config)

