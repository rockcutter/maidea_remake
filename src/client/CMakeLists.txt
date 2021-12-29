#src/client/CMakeLists.txt
add_library(MyClient STATIC MyClient.cpp)

target_link_libraries(MyClient sleepy-discord)
target_link_libraries(MyClient Handler)