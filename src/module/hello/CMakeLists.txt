#src/module/hello
add_library(Module_Hello STATIC Hello.cpp)

target_link_libraries(Module_Hello PRIVATE Essential)
