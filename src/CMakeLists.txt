

add_subdirectory(client)
add_subdirectory(core)
add_subdirectory(handler)
add_subdirectory(module)
add_subdirectory(util)

add_library(Main INTERFACE)
target_link_libraries(Main INTERFACE MyClient)
target_link_libraries(Main INTERFACE Core)
target_link_libraries(Main INTERFACE Handler)
target_link_libraries(Main INTERFACE Module)
target_link_libraries(Main INTERFACE Util)
