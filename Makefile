CC = c99
CFLAGS += -pedantic -Wall -Wextra -Werror

# The deps for the static library, libpcalc
lib: libpcalc.a

libpcalc.a: plate_calc.o
	ar rcs libpcalc.a plate_calc.o

plate_calc.o: plate_calc.c plate_calc.h
	$(CC) $(CFLAGS) -c plate_calc.c

# The deps for the tests
test: lib pcalc_test
	./pcalc_test

pcalc_test: pcalc_test.o
	$(CC) -o pcalc_test pcalc_test.o libpcalc.a

pcalc_test.o: pcalc_test.c
	$(CC) $(CFLAGS) -c pcalc_test.c


clean:
	rm -f pcalc_test libpcalc.a *.o