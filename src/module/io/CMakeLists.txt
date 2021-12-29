add_library(Module_IOModule STATIC IOModule.cpp IOModule.h)

target_link_libraries(Module_IOModule sleepy-discord)

target_include_directories(Handler PUBLIC ${PROJECT_SOURCE_DIR}/src)