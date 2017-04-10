#include <stdlib.h>
#include <assert.h>

#include "plate_calc.h"

static int
plates_equal(float actual[], float expected[])
{
	for(int i = 0; (actual[i] != 0 || expected[i] != 0); i++) {
		if(actual[i] != expected[i])
			return 0;
	}
	return 1;
}

int main()
{
	const float bar_weight = 45;
	// Decision: list of plates pre-sorted from highest to lowest and ends with
	// zero sentinel. 
	const float plates_avail[] = {45, 35, 25, 15, 10, 5, 2.5, 1.5, 0};

	// Calculate plates for 100 lb load
	float *actual = calc_plates(100, bar_weight, plates_avail);
	assert(actual);

	float expected[] = {25, 2.5, 0};
	assert(plates_equal(actual, expected));

	free(actual);

	return 0;
}