project(VindleBoy_Emulator)

find_package(SDL2 REQUIRED)

add_executable(main Main.cpp bus.cpp cart.cpp cpu.cpp emu.cpp ppu.cpp timer.cpp)
target_link_libraries(main PRIVATE SDL2::SDL2)
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})