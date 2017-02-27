set_directive_interface -mode s_axilite -bundle ctrl "led_controller" config
set_directive_interface -mode s_axilite -bundle ctrl "led_controller"

set_directive_interface -mode ap_none "led_controller" led_o
set_directive_interface -mode ap_none "led_controller" gp_i

set_directive_array_partition -type complete -dim 1 "led_controller" config
set_directive_array_partition -type complete -dim 1 "led_controller" led_o
set_directive_array_partition -type complete -dim 1 "led_controller" gp_i
set_directive_array_partition -type complete -dim 1 "led_controller" handles

set_directive_pipeline -II 1 "handle"
set_directive_dataflow "led_controller"
set_directive_unroll "led_controller/LOOP"
