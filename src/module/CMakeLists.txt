#src/module
add_library(Module INTERFACE)

add_subdirectory(io)
add_subdirectory(base)

target_link_libraries(Module INTERFACE Module_ModuleBase)
target_link_libraries(Module INTERFACE Module_IOModule)
