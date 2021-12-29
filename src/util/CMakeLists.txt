add_library(Util INTERFACE)

add_subdirectory(config)

add_library(ConsoleOut ConsoleOut.cpp ConsoleOut.h)

target_link_libraries(Util INTERFACE ConsoleOut)
target_link_libraries(Util INTERFACE Config)

target_include_directories(Handler PUBLIC ${PROJECT_SOURCE_DIR}/src)
