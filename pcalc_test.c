#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "plate_calc.h"

#define MAX_PLATES_AVAIL 20
#define MAX_PLATES_EXPTD 10

struct test_case {
	float bar_weight;
	float target_weight;
	float plates_avail[MAX_PLATES_AVAIL];
	float expected[MAX_PLATES_EXPTD];
} test_cases[] = {
	{45, 100, {45, 35, 25, 15, 10, 5, 2.5, 1.5, 0}, {25, 2.5, 0}},
	{45, 110, {45, 35, 25, 15, 10, 5, 2.5, 1.5, 0}, {25, 5, 2.5, 0}}
};


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
	const int ncases = sizeof(test_cases) / sizeof(struct test_case);
	printf("Number of test cases: %d\n", ncases);

	for(int i = 0; i < ncases; ++i) {
		float *actual =
			calc_plates(
				test_cases[i].target_weight,
				test_cases[i].bar_weight,
				test_cases[i].plates_avail);

		assert(actual);
		assert(plates_equal(actual, test_cases[i].expected));
		free(actual);
	}

	printf("PASSED\n");

	return 0;
}
