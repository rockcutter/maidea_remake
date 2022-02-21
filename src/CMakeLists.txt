

add_subdirectory(client)
add_subdirectory(handler)
add_subdirectory(module)
add_subdirectory(util)

add_library(Main INTERFACE)

add_library(Essential INTERFACE)
find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(Essential INTERFACE sleepy-discord)
target_include_directories(Essential INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(Essential INTERFACE ${Boost_LIBRALIES})


target_link_libraries(Main INTERFACE MyClient)
target_link_libraries(Main INTERFACE Handler)
target_link_libraries(Main INTERFACE Module)
target_link_libraries(Main INTERFACE Util)

target_link_libraries(Module INTERFACE sleepy-discord)

target_include_directories(MyClient PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Handler PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Util PUBLIC INTERFACE ${PROJECT_SOURCE_DIR}/src)

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(Main INTERFACE ${Boost_LIBRARIES})
target_link_libraries(Main INTERFACE Boost::program_options)
