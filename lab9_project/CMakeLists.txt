add_executable(lab9.elf main.c gameControl.c piece.c)
target_link_libraries(lab9.elf ${330LIBS} interrupts intervalTimer buttons_switches)
set_target_properties(lab9.elf PROPERTIES LINKER_LANGUAGE CXX)