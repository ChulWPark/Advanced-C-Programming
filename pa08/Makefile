CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa08.o solver.o
VALG = valgrind --tool=memcheck --leak-check=full
# You need to write this file so that
#
# "make"" will create an executable called pa08
all: $(OBJS)
	$(GCC) $(OBJS) maze.o path.o -o pa08 

pa08.o: pa08.c maze.h path.h solver.c solver.h
	$(GCC) -c pa08.c

solver.o: pa08.c maze.h path.h solver.c solver.h
	$(GCC) -c solver.c
#.o.c: 
#   $(GCC) $(DTEST) -c $*.c

# "make test" will run maze files
test: all 
	./pa08 inputs/maze1
	./pa08 inputs/maze2
	./pa08 inputs/maze3
	./pa08 inputs/maze4
	./pa08 inputs/maze5
	./pa08 inputs/maze6
	./pa08 inputs/maze7
	./pa08 inputs/maze8
	./pa08 inputs/maze9
# "make memory" calls valgrind to check memory errors

memory: all test
	$(VALG) ./pa08 inputs/maze1
	$(VALG) ./pa08 inputs/maze2
	$(VALG) ./pa08 inputs/maze3
	$(VALG) ./pa08 inputs/maze4
	$(VALG) ./pa08 inputs/maze5
	$(VALG) ./pa08 inputs/maze6
	$(VALG) ./pa08 inputs/maze7
	$(VALG) ./pa08 inputs/maze8
	$(VALG) ./pa08 inputs/maze9

# "make clean" remove .o and all output files

clean:
	/bin/rm -f pa08.o solver.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa08
