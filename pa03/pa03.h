// * DO NOT MODIFY THIS FILE * 
// If you modify this file, your program may be incompatible
// in grading and you may lose points.
// 
#ifndef PA03_H
#define PA03_H
typedef struct
{
  double upperlimit;
  double lowerlimit;
  int intervals;
} Range;

typedef struct
{
  Range rng; 
  double answer;
} RangeAnswer;

double func(double xval);  // the function to be integrated

#ifdef INTEGRATE_1
// the first integration function returns the result
double integrate1(Range rng);
#endif

#ifdef INTEGRATE_2
// the second integration function stores the result
// in the pointer
void integrate2(RangeAnswer * rngans);
#endif

#endif
