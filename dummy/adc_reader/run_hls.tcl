open_project -reset adc_reader

set_top adc_reader

add_files "adc_reader.h adc_reader.c"

open_solution -reset "solution1"
set_part {xc7z010clg400-1}
create_clock -period 125MHz -name default
source "./directives.tcl"

csynth_design
export_design -format ip_catalog -evaluate verilog

exit
