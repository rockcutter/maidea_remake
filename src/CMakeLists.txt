

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

target_include_directories(MyClient PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Core PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Handler PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Util PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)


find_package(Boost REQUIRED)
target_link_libraries(Main INTERFACE ${Boost_LIBRARIES})
