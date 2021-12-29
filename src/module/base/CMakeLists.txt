#src/module/base

add_library(Module_ModuleBase ModuleBase.cpp ModuleBase.h)

target_link_libraries(Module_ModuleBase sleepy-discord)