#src/module/io
add_library(Module_IOModule STATIC IOModule.cpp)

target_link_libraries(Module_IOModule sleepy-discord)
