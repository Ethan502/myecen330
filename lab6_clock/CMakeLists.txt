add_executable(lab6.elf main.c clockDisplay.c clockControl.c)
target_link_libraries(lab6.elf ${330LIBS} touchscreen interrupts intervalTimer)
set_target_properties(lab6.elf PROPERTIES LINKER_LANGUAGE CXX)