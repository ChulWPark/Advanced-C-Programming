CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa11.o calc.o
VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

# "make"" will create an executable called pa11
all: $(OBJS)
	$(GCC) $(OBJS) -o pa11

pa11.o: pa11.c calc.c calc.h
	$(GCC) -c pa11.c

calc.o: pa11.c calc.c calc.h
	$(GCC) -c calc.c

#.o.c: 
#   $(GCC) $(DTEST) -c $*.c

# "make test" will test files
test: all 
	./pa11 inputs/test1
	./pa11 inputs/test2
	./pa11 inputs/test3
	-./pa11 inputs/test4
	-./pa11 inputs/test5

# "make memory" calls valgrind to check memory errors
memory: all test
	$(VALG) ./pa11 inputs/test1
	$(VALG) ./pa11 inputs/test2
	$(VALG) ./pa11 inputs/test3
	$(VALG) ./pa11 inputs/test4
	$(VALG) ./pa11 inputs/test5

# "make clean" remove .o and all output files
clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa11
