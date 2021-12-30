#src/module/hello
add_library(Module_Hello STATIC Hello.cpp)

target_link_libraries(Module_Hello sleepy-discord)

target_link_libraries(Module_Hello Module_ModuleBase)
