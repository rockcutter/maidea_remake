#src/module/base

add_library(Module_ModuleBase STATIC ModuleBase.cpp )

target_link_libraries(Module_ModuleBase sleepy-discord)
