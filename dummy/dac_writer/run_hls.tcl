open_project -reset dac_writer

set_top dac_writer

add_files "dac_writer.h dac_writer.c"

open_solution -reset "solution1"
set_part {xc7z010clg400-1}
create_clock -period 125MHz -name default
source "./directives.tcl"

csynth_design
export_design -format ip_catalog -evaluate verilog

exit
