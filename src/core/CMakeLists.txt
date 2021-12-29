add_library(Core INTERFACE)

add_subdirectory(commandParser)

target_link_libraries(Core INTERFACE CommandParser)
