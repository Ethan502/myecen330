add_executable(lab7_m2.elf main_m2.c testBoards.c minimax.c ticTacToeControl.c ticTacToeDisplay.c)
target_link_libraries(lab7_m2.elf ${330LIBS} touchscreen interrupts intervalTimer buttons_switches)
set_target_properties(lab7_m2.elf PROPERTIES LINKER_LANGUAGE CXX)