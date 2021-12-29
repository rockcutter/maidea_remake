#src/handler/CMakeLists.txt
add_library(Handler STATIC CommandHandler.cpp MessageHandler.cpp )

target_link_libraries(Handler sleepy-discord)
target_link_libraries(Handler Module)