add_executable(lab8_m1.elf main_m1.c missile.c)
target_link_libraries(lab8_m1.elf ${330LIBS} touchscreen interrupts intervalTimer)
set_target_properties(lab8_m1.elf PROPERTIES LINKER_LANGUAGE CXX)