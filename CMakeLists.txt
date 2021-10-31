#CMakeLists.txt
cmake_minimum_required (VERSION 3.6)
project(maidea)

add_executable(maidea "src/main.cpp" "src/main.h" "src/util/ConsoleOut.cpp" "src/util/ConsoleOut.h" "src/handler/MessageHandler.cpp" "src/handler/MessageHandler.h" "src/client/MyClient.cpp" "src/client/MyClient.h" "src/handler/CommandHandler.cpp" "src/handler/CommandHandler.h")

add_executable(all_purpose_test "src/test/test.cpp" "src/test/test.h")

add_subdirectory(sleepy-discord)
target_link_libraries(maidea sleepy-discord)
target_link_libraries(all_purpose_test sleepy-discord)

