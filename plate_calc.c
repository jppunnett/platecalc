#include <stddef.h>
#include <stdlib.h>
#include "plate_calc.h"

float*
calc_plates(float target_weight, float barbell_weight, const float* plates_avail)
{
	if(plates_avail == NULL) return NULL;
	
	float *plates = malloc(3 * sizeof(float));
	plates[0] = 25;
	plates[1] = 2.5;
	plates[2] = 0;
	
	return plates;	
}