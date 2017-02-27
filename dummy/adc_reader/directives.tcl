set_directive_interface -mode s_axilite -bundle ctrl "adc_reader"

set_directive_pipeline -II 1 "adc_reader"

set_directive_interface -mode axis "adc_reader" out
