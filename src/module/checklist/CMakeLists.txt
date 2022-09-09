add_library(Module_Checklist STATIC Checklist.cpp)

target_link_libraries(Module_Checklist PRIVATE Essential)
target_link_libraries(Module_Checklist PRIVATE Module_ModuleBase)

target_include_directories(Module_Checklist PUBLIC ${PROJECT_SOURCE_DIR}/src/module/base)
