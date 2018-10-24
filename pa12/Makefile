CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa12.o expressionTree.o scanner.o tree.o
VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

# You need to write this file so that
#
# "make"" will create an executable called pa12
all: $(OBJS)
	$(GCC) $(OBJS) -o pa12

pa12.o: pa12.c expressionTree.c expressionTree.h scanner.c scanner.h tree.c tree.h
	$(GCC) -c pa12.c

expressionTree.o: pa12.c expressionTree.c expressionTree.h scanner.c scanner.h tree.c tree.h
	$(GCC) -c expressionTree.c

scanner.o: pa12.c expressionTree.c expressionTree.h scanner.c scanner.h tree.c tree.h
	$(GCC) -c scanner.c

tree.o: pa12.c expressionTree.c expressionTree.h scanner.c scanner.h tree.c tree.h
	$(GCC) -c tree.c

#.o.c: 
#   $(GCC) $(DTEST) -c $*.c

# "make test" will run pa12
test: all 
	./pa12 inputs/test1 output1
	./pa12 inputs/test2 output2
	./pa12 inputs/test3 output3
	./pa12 inputs/test4 output4
	./pa12 inputs/test5 output5

# "make memory" calls valgrind to check memory errors
memory: all test
	$(VALG) ./pa12 inputs/test1 output1
	$(VALG) ./pa12 inputs/test2 output2
	$(VALG) ./pa12 inputs/test3 output3
	$(VALG) ./pa12 inputs/test4 output4
	$(VALG) ./pa12 inputs/test5 output5

# "make clean" remove .o and all output files
clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa12
	/bin/rm -f output1 output2 output3 output4 output5
