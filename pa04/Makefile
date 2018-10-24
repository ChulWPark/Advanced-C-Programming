CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(CFLAGS) $(COVFLAGS) $(PROFFLAG)
OBJS = pa04.o answer04.o
FUNCS = func1.o func2.o func3.o func4.o func5.o

pa04: $(OBJS) $(FUNCS)
	$(GCC) $(OBJS) $(FUNCS) -o pa04 -lm

pa04.o: pa04.c pa04.h
	$(GCC) -c -DRUN_INTEGRATE -DTEST_INTEGRATE pa04.c -o pa04.o

answer04.o: answer04.c pa04.h
	$(GCC) -c -DRUN_INTEGRATE -DTEST_INTEGRATE answer04.c -o answer04.o

%.o : %.c
	$(GCC) -c $(CFLAGS) $<

testall: pa04
		./pa04 testdir/test1 output_test1
		./pa04 testdir/test2 output_test2
		./pa04 testdir/test3 output_test3
		./pa04 testdir/test4 output_test4
		./pa04 testdir/test5 output_test5
clean:
	/bin/rm -f input*
	/bin/rm -f *.o
	/bin/rm -f testgen 
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa04 pa04.prof
	/bin/rm -f output_test1 output_test2 output_test3 output_test4 output_test5


