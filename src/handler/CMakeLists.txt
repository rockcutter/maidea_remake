#src/handler/CMakeLists.txt
add_library(Handler STATIC Handler.cpp)

target_link_libraries(Handler PRIVATE sleepy-discord)
target_link_libraries(Handler PRIVATE Module)
target_link_libraries(Handler PRIVATE Essential)