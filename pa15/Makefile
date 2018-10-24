CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = pa15.o huffman.o
VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

# "make"" will create an executable called pa14
all: $(OBJS)
	$(GCC) $(OBJS) -o pa15

pa15.o: pa15.c huffman.c huffman.h
	$(GCC) -c pa15.c

huffman.o: pa15.c huffman.c huffman.h
	$(GCC) -c huffman.c

#.o.c: 
#   $(GCC) $(DTEST) -c $*.c

# "make test" will run pa14
test: all
	./pa15 inputs/gophers outputs/gophers_sorted outputs/gophers_huffman outputs/gophers_header 
	./pa15 inputs/basic outputs/basic_sorted outputs/basic_huffman outputs/basic_header
	./pa15 inputs/para outputs/para_sorted outputs/para_huffman outputs/para_header
	./pa15 inputs/prideandprejudice outputs/prideandprejudice_sorted outputs/prideandprejudice_huffman outputs/prideandprejudice_header
	./pa15 inputs/woods outputs/woods_sorted outputs/woods_huffman outputs/woods_header
	./pa15 inputs/aaaaa aaaaa_sorted aaaaa_huffman aaaaa_header

# "make memory" calls valgrind to check memory errors
memory: all test
	$(VALG) ./pa15 inputs/gophers outputs/gophers_sorted outputs/gophers_huffman outputs/gophers_header
	$(VALG) ./pa15 inputs/basic outputs/basic_sorted outputs/basic_huffman outputs/basic_header
	$(VALG) ./pa15 inputs/para outputs/para_sorted outputs/para_huffman outputs/para_header
	$(VALG) ./pa15 inputs/prideandprejudice outputs/prideandprejudice_sorted outputs/prideandprejudice_huffman outputs/prideandprejudice_header
	$(VALG) ./pa15 inputs/woods outputs/woods_sorted outputs/woods_huffman outputs/woods_header
	$(VALG) ./pa15 inputs/aaaaa aaaaa_sorted aaaaa_huffman aaaaa_header

# "make compare" compares between output files and expected files
compare:
	diff outputs/gophers_sorted expected/gophers_sorted
	diff outputs/basic_sorted expected/basic_sorted
	diff outputs/para_sorted expected/para_sorted
	diff outputs/prideandprejudice_sorted expected/prideandprejudice_sorted
	diff outputs/woods_sorted expected/woods_sorted
	diff outputs/gophers_huffman expected/gophers_huffman
	diff outputs/basic_huffman expected/basic_huffman
	diff outputs/para_huffman expected/para_huffman
	diff outputs/prideandprejudice_huffman expected/prideandprejudice_huffman
	diff outputs/woods_huffman expected/woods_huffman

# "make clean" remove .o and all output files
clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa15
	/bin/rm -f outputs/gophers_sorted outputs/gophers_huffman outputs/gophers_header
	/bin/rm -f outputs/basic_sorted outputs/basic_huffman outputs/basic_header
	/bin/rm -f outputs/para_sorted outputs/para_huffman outputs/para_header
	/bin/rm -f outputs/prideandprejudice_sorted outputs/prideandprejudice_huffman outputs/prideandprejudice_header
	/bin/rm -f outputs/woods_sorted outputs/woods_huffman outputs/woods_header
	/bin/rm -f aaaaa_sorted aaaaa_huffman aaaaa_header
