CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa10.o list.o maze.o mazehelper.o path.o solver.o
VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes
# You need to write this file so that
#
# "make"" will create an executable called pa08
all: $(OBJS)
	$(GCC) $(OBJS) -o pa10 

pa10.o: pa10.c list.c list.h maze.c maze.h mazehelper.c mazehelper.h path.c path.h solver.c solver.h
	$(GCC) -c pa10.c

list.o: pa10.c list.c list.h maze.c maze.h mazehelper.c mazehelper.h path.c path.h solver.c solver.h
	$(GCC) -c list.c

maze.o: pa10.c list.c list.h maze.c maze.h mazehelper.c mazehelper.h path.c path.h solver.c solver.h
	$(GCC) -c maze.c

mazehelper.o: pa10.c list.c list.h maze.c maze.h mazehelper.c mazehelper.h path.c path.h solver.c solver.h
	$(GCC) -c mazehelper.c

path.o: pa10.c list.c list.h maze.c maze.h mazehelper.c mazehelper.h path.c path.h solver.c solver.h
	$(GCC) -c path.c

solver.o: pa10.c list.c list.h maze.c maze.h mazehelper.c mazehelper.h path.c path.h solver.c solver.h
	$(GCC) -c solver.c


#.o.c: 
#   $(GCC) $(DTEST) -c $*.c

# "make test" will run maze files
test: all 
	./pa10 inputs/maze1 output1
	./pa10 inputs/maze2 output2
	./pa10 inputs/maze3 output3
	./pa10 inputs/maze4 output4
	./pa10 inputs/maze5 output5
	./pa10 inputs/maze6 output6

# "make memory" calls valgrind to check memory errors
memory: all test
	$(VALG) ./pa10 inputs/maze1 output1
	$(VALG) ./pa10 inputs/maze2 output2
	$(VALG) ./pa10 inputs/maze3 output3
	$(VALG) ./pa10 inputs/maze4 output4
	$(VALG) ./pa10 inputs/maze5 output5
	$(VALG) ./pa10 inputs/maze6 output6

# "make clean" remove .o and all output files
clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa10
	/bin/rm -f output1 output2 output3 output4 output5 output6
