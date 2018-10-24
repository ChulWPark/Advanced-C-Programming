CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa07.o maze.o path.o
VALG = valgrind --tool=memcheck --leak-check=full
# You need to write this file so that
#
# "make"" will create an executable called pa06
all: $(OBJS)
	$(GCC) $(OBJS) -o pa07 

pa07.o: pa07.c maze.c maze.h path.c path.h
	$(GCC) -c pa07.c

maze.o: pa07.c maze.c maze.h path.c path.h
	$(GCC) -c maze.c

path.o: pa07.c maze.c maze.h path.c path.h 
	$(GCC) -c path.c

#.o.c: 
#	$(GCC) $(DTEST) -c $*.c

# "make test" will run the three input files 
test: all
	./pa07 inputs/maze1 inputs/path1
	./pa07 inputs/maze1 inputs/path1-bad1
	./pa07 inputs/maze1 inputs/path1-bad2
	./pa07 inputs/maze2 inputs/path2
	./pa07 inputs/maze2 inputs/path2-bad1
	./pa07 inputs/maze3 inputs/path3
	./pa07 inputs/maze3 inputs/path3-bad1
	./pa07 inputs/maze4 inputs/path4
	./pa07 inputs/maze4 inputs/path4-bad1
	./pa07 inputs/maze5 inputs/path5

# "make memory" calls valgrind to check memory errors

memory: all test
	$(VALG) ./pa07 inputs/maze1 inputs/path1
	$(VALG) ./pa07 inputs/maze1 inputs/path1-bad1
	$(VALG) ./pa07 inputs/maze1 inputs/path1-bad2
	$(VALG) ./pa07 inputs/maze2 inputs/path2
	$(VALG) ./pa07 inputs/maze2 inputs/path2-bad1
	$(VALG) ./pa07 inputs/maze3 inputs/path3
	$(VALG) ./pa07 inputs/maze3 inputs/path3-bad1
	$(VALG) ./pa07 inputs/maze4 inputs/path4
	$(VALG) ./pa07 inputs/maze4 inputs/path4-bad1
	$(VALG) ./pa07 inputs/maze5 inputs/path5

# "make clean" remove .o and all output files

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa07
