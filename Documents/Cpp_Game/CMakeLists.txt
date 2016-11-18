project(cpp_game)
include_directories(/usr/incude/c++)
add_executable(cpp_game Main.cpp)

install(TARGETS cpp_game RUNTIME DESTINATION bin)
