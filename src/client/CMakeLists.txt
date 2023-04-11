# src/client/CMakeLists.txt

# TODO ソースファイルを追加
set(client_source_file
    ${CMAKE_CURRENT_SOURCE_DIR}/MyClient.cpp
)

add_library(
    client
    STATIC
    ${client_source_file}
)

target_compile_features(client PRIVATE cxx_std_17)
target_compile_options(client PRIVATE
    $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
)

target_link_libraries(client sleepy-discord)