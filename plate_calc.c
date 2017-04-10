#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "plate_calc.h"

static float get_plate_weight(const float weight, const float plates_avail[]);


float*
calc_plates(float target_weight, float bar_weight, const float plates_avail[])
{
	if(plates_avail == NULL) return NULL;
	if(target_weight <= 0) return NULL;
	if(bar_weight <= 0) return NULL;

	// Ten seems a reasonable estimate of the number of plates you can stack on
	// one side of a bar.
	static const int MAX_PLATES = 10;
	float *plates = calloc(MAX_PLATES, sizeof(float));
	if(!plates) return NULL;
	int i = 0;

	// remainder is the weight we need on one side of the bar. E.g. if we want
	// to lift 100lbs using a 45lb bar, remainder would be:
	//   (100 - 45) / 2 = 27.5lbs
	// We need to load 27.5lbs on both sides of a 45lb bar to lift 100lbs.
	float remainder = (target_weight - bar_weight) / 2;
	while(remainder > 0) {
		float plate = get_plate_weight(remainder, plates_avail);
		remainder -= plate;
		if(remainder >= 0) {
			if(i < MAX_PLATES)
				plates[i++] = plate;
		}
	}
	return plates;	
}

static float
get_plate_weight(float weight, const float plates_avail[])
{
	assert(weight > 0);
	assert(plates_avail != NULL);
	int i = 0;
	for(; plates_avail[i] != 0; ++i) {
		if((weight - plates_avail[i]) >= 0)
			return plates_avail[i];
	}
	// Return lightest plate available.
	return plates_avail[i-1];
}
