#src/module/hello
add_library(Module_Hello Hello.cpp)

target_link_libraries(Module INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(Module_Hello Module_IOModule)
target_link_libraries(Module_Hello Module_ModuleBase)

target_link_libraries(Module_Hello sleepy-discord)
