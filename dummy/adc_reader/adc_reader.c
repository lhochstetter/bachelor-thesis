#include <ap_cint.h>

#include "adc_reader.h"

void adc_reader(uint14 in, uint14 *out)
{
	*out = (~in) + 1;
}
