CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = bmp.o filter.o pa13.o
VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

# "make"" will create an executable called pa13
all: $(OBJS)
	$(GCC) $(OBJS) -o pa13

validate.o: validate.c bmp.c bmp.h filter.c filter.h
	$(GCC) -c validate.c

pa13.o: pa13.c bmp.c bmp.h filter.c filter.h
	$(GCC) -c pa13.c

bmp.o: validate.c bmp.c bmp.h filter.c filter.h
	$(GCC) -c bmp.c

filter.o: validate.c bmp.c bmp.h filter.c filter.h
	$(GCC) -c filter.c
#.o.c: 
#   $(GCC) $(DTEST) -c $*.c

# "make test" will run pa13
test: all
	./pa13 test.bmp output.bmp sharpen.filter
#	./pa13 test.bmp output.bmp sharpen.filter
# "make memory" calls valgrind to check memory errors
memory: all test
	$(VALG) ./pa13 test.bmp output.bmp sharpen.filter
#	$(VALG) ./pa13 test.bmp output.bmp sharpen.filter
# "make clean" remove .o and all output files
clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f validate pa13
#	/bin/rm -f output.bmp
