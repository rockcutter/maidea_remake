#src/module
add_library(Module INTERFACE)

add_subdirectory(base)
add_subdirectory(hello)
add_subdirectory(timer)
add_subdirectory(urlshortening)
add_subdirectory(checklist)
add_subdirectory(random)
add_subdirectory(role)
add_subdirectory(possession)

target_link_libraries(Module INTERFACE Module_ModuleBase)
target_link_libraries(Module INTERFACE Module_Hello)
target_link_libraries(Module INTERFACE Module_Timer)
target_link_libraries(Module INTERFACE Module_URLShortening)
target_link_libraries(Module INTERFACE Module_Checklist)
target_link_libraries(Module INTERFACE Module_Role)
target_link_libraries(Module INTERFACE Module_Possession)


target_include_directories(Module_ModuleBase PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module_Hello PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module_Timer PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module_URLShortening PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module_Checklist PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module_Random PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module_Role PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(Module_Possession PUBLIC ${PROJECT_SOURCE_DIR}/src)

