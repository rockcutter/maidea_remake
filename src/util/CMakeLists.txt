add_library(Util INTERFACE)

add_library(ConsoleOut ConsoleOut.cpp)

target_link_libraries(Util INTERFACE ConsoleOut)

