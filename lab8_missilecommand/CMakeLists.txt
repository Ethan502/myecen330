add_executable(lab8_m3.elf main_m2.c missile.c gameControl.c plane.c)
target_link_libraries(lab8_m3.elf ${330LIBS} touchscreen interrupts intervalTimer)
set_target_properties(lab8_m3.elf PROPERTIES LINKER_LANGUAGE CXX)