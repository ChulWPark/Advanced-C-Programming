CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(CFLAGS) $(COVFLAGS) $(PROFFLAG) -DDEBUG
OBJS =  pa01main.o selectsort.o quicksort.o swap.o printarray.o

pa01: testgen $(OBJS)
	$(GCC) $(OBJS) -o pa01

testsome: pa01
	./pa01 input0
	./pa01 input1
	./pa01 input5
	./pa01 input13
	./pa01 input41
	./pa01 input97

testall: testsome
	./pa01 input1021
	./pa01 input16383
	./pa01 input65533
	./pa01 input262143
	./pa01 input1048573

inspect: pa01 
	./pa01 input16383
	gcov selectsort.c
	gprof pa01 > pa01.prof

pa01main.o: pa01main.c pa01.h
	$(GCC) -DSELECTION_SORT -DQUICK_SORT -c pa01main.c

selectsort.o: selectsort.c pa01.h
	$(GCC) -DSELECTION_SORT -c selectsort.c

quicksort.o: quicksort.c pa01.h
	$(GCC) -DQUICK_SORT -c quicksort.c

swap.o: swap.c
	$(GCC) -c swap.c

printarray.o: printarray.c
	$(GCC) -c printarray.c

testgen: testgen.c
	$(GCC) testgen.c -o testgen
	./testgen

clean:
	/bin/rm -f input*
	/bin/rm -f *.o
	/bin/rm -f testgen 
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa01 pa01.prof



