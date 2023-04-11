# src/module/CMakeLists.txt

# TODO ソースファイルを追加
set(module_source_file
    ${CMAKE_CURRENT_SOURCE_DIR}/base/ModuleBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/checklist/Checklist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hello/Hello.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/possession/Possession.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/random/Random.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/role/Role.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/urlshortening/URLShortening.cpp
)

add_library(
    module
    STATIC
    ${module_source_file}
)

target_compile_features(module PRIVATE cxx_std_17)
target_compile_options(module PRIVATE
    $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
)

target_link_libraries(module sleepy-discord)
