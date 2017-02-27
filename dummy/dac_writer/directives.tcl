set_directive_interface -mode s_axilite -bundle ctrl "dac_writer"

set_directive_pipeline -II 1 "dac_writer"

set_directive_interface -mode axis "dac_writer" in
set_directive_interface -mode ap_none "dac_writer" out

