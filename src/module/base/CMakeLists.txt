#src/module/base

add_library(Module_ModuleBase STATIC ModuleBase.cpp)

target_link_libraries(Module_ModuleBase sleepy-discord)
target_include_directories(Module_ModuleBase PUBLIC ${PROJECT_SOURCE_DIR}/src)