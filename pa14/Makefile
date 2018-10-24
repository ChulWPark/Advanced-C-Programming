CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
LFLAGS = -lpthread
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) $(LFLAGS) #$(PROFFLAG)
OBJS = pa14.o bmp.o filterParallel.o
VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

# "make"" will create an executable called pa14
all: $(OBJS)
	$(GCC) $(OBJS) -o pa14

validate.o: validate.c bmp.c bmp.h filterParallel.c filterParallel.h
	$(GCC) -c validate.c

pa14.o: pa14.c bmp.c bmp.h filterParallel.c filterParallel.h
	$(GCC) -c pa14.c

bmp.o: pa14.c validate.c bmp.c bmp.h filterParallel.c filterParallel.h
	$(GCC) -c bmp.c

filterParallel.o: pa14.c validate.c bmp.c bmp.h filterParallel.c filterParallel.h
	$(GCC) -c filterParallel.c

#.o.c: 
#   $(GCC) $(DTEST) -c $*.c

# "make test" will run pa14
test: all
	./pa14 input.bmp output.bmp

# "make memory" calls valgrind to check memory errors
memory: all test
	$(VALG) ./pa14 input.bmp output.bmp

# "make clean" remove .o and all output files
clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa14
	/bin/rm -f output.bmp
