# src/util/CMakeLists.txt

# TODO ソースファイルを追加
set(util_source_file
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleOut.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ReadConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SplitString.cpp
)

add_library(
    util
    STATIC
    ${util_source_file}
)

target_compile_features(util PRIVATE cxx_std_17)
target_compile_options(util PRIVATE
    $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
)

target_link_libraries(util sleepy-discord)