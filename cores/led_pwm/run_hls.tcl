open_project -reset led_pwm

set_top led_pwm

add_files "led_pwm.h led_pwm.c"

add_files -tb "../../testbench/testbench.c ../../testbench/test.h"

add_files -tb test.c -cflags "-I../../testbench/"

open_solution -reset "solution1"
set_part {xc7z010clg400-1}
create_clock -period 100MHz -name default
source "./directives.tcl"

csim_design
csynth_design
cosim_design
export_design -format ip_catalog -evaluate verilog

exit
