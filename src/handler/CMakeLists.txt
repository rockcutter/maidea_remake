add_library(Handler STATIC CommandHandler.cpp CommandHandler.h MessageHandler.cpp MessageHandler.h)

target_link_libraries(Handler sleepy-discord)
