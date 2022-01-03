add_library(Module_Timer STATIC timer.cpp)

find_package(Boost REQUIRED COMPONENTS program_options)
target_include_directories(Module_Timer PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(Module_Timer PRIVATE ${Boost_LIBRALIES})

target_link_libraries(Module_Timer PRIVATE sleepy-discord)