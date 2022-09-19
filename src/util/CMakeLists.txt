add_library(Util STATIC ConsoleOut.cpp MultipleUnique.h ReadConfig.cpp)

#add_library(ConsoleOut ConsoleOut.cpp  "MultipleUnique.h" "ReadConfig.cpp")

target_link_libraries(Util PRIVATE Essential)

