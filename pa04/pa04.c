// You must modify this file
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pa04.h"
#define TOLERANCE 0.1 // acceptable difference in floating point numbers

// --------------------------------------------------------------
// write the main fuunction
// the main function should return an integer
// It has two arguments:
//     first int called "argc"
//     seond is char * * called "argv"
// The function returns EXIT_SUCCESS or EXIT_FAILURE (not 0 or 1)

// The function expects two arguments; thus, argc must be three 
// argv[0] is always the name of the program
// argv[1] is the name for the input file
// argv[2] is the name for the output file
int main(int argc, char * * argv)
{
  // check whether argc is 3
  // If argc is not argc, return EXIT_FAILURE

	if(argc != 3)
	{
		return EXIT_FAILURE;
	}

  // call runIntegrate with argv[1] and argv[2]
  // runIntegrate may return true or false
  // If runIntegrate returns false, main returns EXIT_FAILURE

	if(runIntegrate(argv[1], argv[2]) == false)
	{
		return EXIT_FAILURE;
	}

  // other return EXIT_SUCCESS
    printf("Successfully Integrated\n");
	return EXIT_SUCCESS;

}
