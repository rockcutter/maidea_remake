cmake_minimum_required(VERSION 3.6)
enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#FetchContentを使うぞ
include(FetchContent)

# TODO project_nameを書き換える
project(maidea)

# TODO ソースを追加
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

#ディレクトリ分割
include_directories(
    ${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(sleepy-discord)
add_subdirectory(src)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sleepy-discord)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE client)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE util)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE module)

# spdlog導入
FetchContent_Declare(
    spdlog 
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x
)

FetchContent_MakeAvailable(spdlog)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC spdlog::spdlog)

# sleepydiscord導入
FetchContent_Declare(
    SleepyDiscord 
    GIT_REPOSITORY https://github.com/yourWaifu/sleepy-discord.git
)

FetchContent_MakeAvailable(spdlog)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC spdlog::spdlog)