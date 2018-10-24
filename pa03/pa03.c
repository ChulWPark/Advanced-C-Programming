// * DO NOT MODIFY THIS FILE * 
// If you modify this file, your program may be incompatible
// in grading and you may lose points.
// 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pa03.h"
#define TOLERANCE 0.1 // acceptable difference in floating point numbers

static bool checkValue(double expected, double reported, double tolerance)
{
  double difference = expected - reported;
  // make it positive
  if (difference < 0)
    {
      difference = - difference; 
    }
#ifdef DEBUG
   printf("expected = %f, answer = %f, difference = %f\n",
	  expected, reported, difference);
#endif
  if (difference > tolerance)
    {
      return false;
    }
  return true;
}

// return true if the integration result is close to the expected answer
// return false when encountering any problem
static bool testIntegrate(char * filename)
{
  FILE * fptr = fopen(filename, "r");
   if (fptr == NULL)
    {
      fprintf(stderr, "fopen fail\n");
      return false;
    }
   Range rng;
   double expected;
   fscanf(fptr, "%lf\n", & rng.lowerlimit);
   fscanf(fptr, "%lf\n", & rng.upperlimit);
   fscanf(fptr, "%d\n", & rng.intervals);
   fscanf(fptr, "%lf\n", & expected);
   fclose (fptr);
   double ans = 0;
   bool correct = false;
#ifdef INTEGRATE_1
   ans = integrate1(rng);
   correct = checkValue(ans, expected, TOLERANCE);
#endif
#ifdef INTEGRATE_2
   RangeAnswer rngans;
   rngans.rng = rng;
   integrate2(& rngans);
   ans = rngans.answer;
   correct = checkValue(ans, expected, TOLERANCE);
#endif

	printf("Lower bound: %f\n", rng.lowerlimit);
	printf("Upper bound: %f\n", rng.upperlimit);
	printf("# intervals: %d\n", rng.intervals);
	printf("Exected answer: %f\n", expected);
	printf("Your answer: %f\n", ans);

   return correct;
}

// --------------------------------------------------------------
int main(int argc, char * * argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "need the name of an input file\n");
      return EXIT_FAILURE;
    }
  if (testIntegrate(argv[1]) == false)
    {
      fprintf(stderr, "testIntegrate fail\n");
      return EXIT_FAILURE;
    }
  printf("Integration matched!\n");
  return EXIT_SUCCESS;
}
