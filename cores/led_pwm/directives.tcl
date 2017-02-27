set_directive_interface -mode s_axilite -bundle ctrl "led_pwm" led
set_directive_interface -mode s_axilite -bundle ctrl "led_pwm" threshold_on
set_directive_interface -mode s_axilite -bundle ctrl "led_pwm" threshold_off
set_directive_interface -mode s_axilite -bundle ctrl "led_pwm"

set_directive_pipeline -II 1 "led_pwm"
