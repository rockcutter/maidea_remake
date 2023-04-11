cmake_minimum_required(VERSION 3.6)
enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO project_nameを書き換える
project(maidea)

set(proj_src
    src/main.cpp
    src/Initialize.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${proj_src})

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
    $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(sleepy-discord)
add_subdirectory(src)

target_link_libraries(${CMAKE_PROJECT_NAME} sleepy-discord)
target_link_libraries(${CMAKE_PROJECT_NAME} client)
target_link_libraries(${CMAKE_PROJECT_NAME} util)
target_link_libraries(${CMAKE_PROJECT_NAME} module)


# #CMakeLists.txt
# cmake_minimum_required (VERSION 3.6)
# project(maidea)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(maidea "src/main.cpp" "src/Initialize.cpp" )

# #add_executable(all_purpose_test  "src/test/test.cpp" "src/test/test.h" "src/util/ConsoleOut.cpp" "src/util/ConsoleOut.h" "src/handler/MessageHandler.cpp" "src/handler/MessageHandler.h" "src/client/MyClient.cpp" "src/client/MyClient.h" "src/handler/CommandHandler.cpp" "src/handler/CommandHandler.h" "src/module/BaseModule.cpp" "src/module/BaseModule.h" "src/module/io/IOModule.cpp" "src/module/io/IOModule.h" "src/util/config/Config.cpp" "src/util/config/Config.h" "src/core/commandParser/ParseCommand.h" "src/core/commandParser/ParseCommand.cpp")

# add_subdirectory(sleepy-discord)
# add_subdirectory(src)
# target_link_libraries(maidea sleepy-discord)
# target_link_libraries(maidea Main)
# #target_link_libraries(all_purpose_test sleepy-discord)

