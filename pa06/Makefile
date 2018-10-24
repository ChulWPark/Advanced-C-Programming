CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg 
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa06.o student.o msort.o
VALG = valgrind --tool=memcheck --leak-check=full
DTEST = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
# You need to write this file so that
#
# "make"" will create an executable called pa06
all: $(OBJS)
	$(GCC) $(OBJS) $(DTEST) -o pa06 

pa06.o: pa06.c student.c student.h constant.h msort.c msort.h
	$(GCC) -c $(DTEST) pa06.c

msort.o: msort.c pa06.c student.c student.h constant.h msort.h
	$(GCC) -c msort.c

student.o: student.c constant.h student.h
	$(GCC) -c $(DTEST) student.c

#.o.c: 
#	$(GCC) $(DTEST) -c $*.c

# "make test" will run the three input files 
test: all
	./pa06 inputs/testinput1 id1 first1 last1
	./pa06 inputs/testinput2 id2 first2 last2
	./pa06 inputs/testinput3 id3 first3 last3
# input: inputs/testinput1; output: id1, first1, last1
# input: inputs/testinput2; output: id2, first2, last2
# input: inputs/testinput3; output: id3, first3, last3
#
# "make memory" calls valgrind to check memory errors

memory: all test
	$(VALG) ./pa06 inputs/testinput1 id1 first1 last1
	$(VALG) ./pa06 inputs/testinput2 id2 first2 last2
	$(VALG) ./pa06 inputs/testinput3 id3 first3 last3

# "make clean" remove .o and all output files

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa06
	/bin/rm -f id1 id2 id3
	/bin/rm -f first1 first2 first3
	/bin/rm -f last1 last2 last3
