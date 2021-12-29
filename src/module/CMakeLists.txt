add_library(Module INTERFACE)

add_subdirectory(io)
add_library(Module_BaseModule STATIC  BaseModule.cpp BaseModule.h)

target_link_libraries(Module_BaseModule PRIVATE sleepy-discord)

target_link_libraries(Module INTERFACE Module_BaseModule)
target_link_libraries(Module INTERFACE Module_IOModule)
