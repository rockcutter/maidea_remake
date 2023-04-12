# TODO ライブラリ名を追加
set(current_library_name
    util
)

# TODO ソースファイルを追加
set(current_library_source_file
    ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleOut.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ReadConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SplitString.cpp
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

target_link_libraries(${current_library_name} sleepy-discord)