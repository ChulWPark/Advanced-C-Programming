CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa05.o student.o
VALG = valgrind --tool=memcheck --leak-check=full
DTEST = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
# You need to write this file so that
#
# "make"" will create an executable called pa05
all: $(OBJS)
	$(GCC) $(OBJS) -o pa05

pa05.o: pa05.c student.c student.h constant.h
	$(GCC) -c pa05.c

student.o: student.c constant.h student.h
	$(GCC) -c $(DTEST) student.c
# 
#%.o : %.c
#	$(GCC) -c $(CFLAGS) $<
# "make test" will run the three input files 
test: pa05
	./pa05 inputs/testinput1 id1 first1 last1
	./pa05 inputs/testinput2 id2 first2 last2
	./pa05 inputs/testinput3 id3 first3 last3
# input: inputs/testinput1; output: id1, first1, last1
# input: inputs/testinput2; output: id2, first2, last2
# input: inputs/testinput3; output: id3, first3, last3
#
# compare your program's output with the expected ouputs by
# using the "diff" command in Linux
compare:
	diff expected/id1 id1
	diff expected/id2 id2
	diff expected/id3 id3
	diff expected/first1 first1
	diff expected/first2 first2
	diff expected/first3 first3
	diff expected/last1 last1
	diff expected/last2 last2
	diff expected/last3 last3
# "make memory" calls valgrind to check memory errors

memory: all test
	$(VALG) ./pa05 inputs/testinput1 id1 first1 last1
	$(VALG) ./pa05 inputs/testinput2 id2 first2 last2
	$(VALG) ./pa05 inputs/testinput3 id3 first3 last3

# "make clean" remove .o and all output files

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa05
	/bin/rm -f id1 first1 last1
	/bin/rm -f id2 first2 last2
	/bin/rm -f id3 first3 last3
