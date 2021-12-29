add_library(MyClient STATIC MyClient.cpp)

target_link_libraries(MyClient sleepy-discord)

target_include_directories(MyClient PUBLIC ${PROJECT_SOURCE_DIR}/src)
