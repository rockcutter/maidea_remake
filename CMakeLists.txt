#CMakeLists.txt
cmake_minimum_required (VERSION 3.6)
project(maidea)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(maidea "src/main.cpp" "src/Initialize.cpp" )

#add_executable(all_purpose_test  "src/test/test.cpp" "src/test/test.h" "src/util/ConsoleOut.cpp" "src/util/ConsoleOut.h" "src/handler/MessageHandler.cpp" "src/handler/MessageHandler.h" "src/client/MyClient.cpp" "src/client/MyClient.h" "src/handler/CommandHandler.cpp" "src/handler/CommandHandler.h" "src/module/BaseModule.cpp" "src/module/BaseModule.h" "src/module/io/IOModule.cpp" "src/module/io/IOModule.h" "src/util/config/Config.cpp" "src/util/config/Config.h" "src/core/commandParser/ParseCommand.h" "src/core/commandParser/ParseCommand.cpp")

add_subdirectory(sleepy-discord)
add_subdirectory(src)
target_link_libraries(maidea sleepy-discord)
target_link_libraries(maidea Main)
#target_link_libraries(all_purpose_test sleepy-discord)

