add_library(CommandParser STATIC ParseCommand.cpp ParseCommand.h)

target_link_libraries(CommandParser PUBLIC ${PROJECT_SOURCE_DIR}/src)