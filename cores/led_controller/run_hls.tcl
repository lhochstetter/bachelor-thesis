open_project -reset led_controller

set_top led_controller

add_files "led_controller.h led_controller.c" -cflags "-I../../shared/"

open_solution -reset "solution1"
set_part {xc7z010clg400-1}
create_clock -period 100MHz -name default
source "./directives.tcl"

csynth_design
export_design -format ip_catalog -evaluate verilog

exit
