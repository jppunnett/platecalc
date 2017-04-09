#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "plate_calc.h"

static float get_plate_weight(const float weight, const float plates_avail[]);


float*
calc_plates(float target_weight, float barbell_weight,
				const float plates_avail[])
{
	if(plates_avail == NULL) return NULL;
	if(target_weight <= 0) return NULL;
	if(barbell_weight <= 0) return NULL;

	// remainder is weight we need on one side of the barbell. E.g. if we want
	// to lift 100lbs with 45lb barbell, remainder would be:
	//   (100 - 45) / 2 = 27.5lbs
	// We need to load 27.5lbs on both sides of barbell to lift 100lbs.
	printf("target_weight=%f, barbell_weight=%f\n", target_weight, barbell_weight);
	printf("target_weight - barbell_weight=%f\n", target_weight-barbell_weight);
	float remainder = (target_weight - barbell_weight) / 2;
	printf("at start remainder=%f\n", remainder);
	while(remainder > 0) {
		// float plate = find_plate(remainder, plates_avail);
		float plate = get_plate_weight(remainder, plates_avail);
		printf("plate=%f\n", plate);
		remainder -= plate;
		printf("remainder=%f\n", remainder);
		if(remainder >= 0) {
			// TODO add plate to array.
			printf("Adding plate, %f\n", plate);
		}
	}
	
	float *plates = malloc(3 * sizeof(float));
	plates[0] = 25;
	plates[1] = 2.5;
	plates[2] = 0;
	
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
	// Return lightest plate available
	return plates_avail[i-1];
}
