# TODO ライブラリ名を追加
set(current_library_name
    module
)

# TODO ソースファイルを追加
set(current_library_source_file
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
    ${current_library_name}
    STATIC
    ${current_library_source_file}
)

target_compile_features(${current_library_name} PRIVATE cxx_std_17)
target_compile_options(${current_library_name} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
)

target_precompile_headers(maidea PUBLIC ${PROJECT_SOURCE_DIR}/sleepy-discord/include/sleepy_discord/sleepy_discord.h)

target_link_libraries(${current_library_name} sleepy-discord)