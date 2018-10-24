// You must modify this file
#ifndef PA04_H
#define PA04_H

// declaring five functions to be integrated
double func1(double);
double func2(double);
double func3(double);
double func4(double);
double func5(double);

// Create a data type called funcptr for function pointers
// The type returns double and takes one double argument
// It must be called "funcptr" and must not use any other name.

typedef double (*funcptr)(double);	// ?????

// create a structure type that has the following attributes
// please make sure the names are exactly the same
//  double- upperlimit;
//  double- lowerlimit;
//  int- intervals;
//  double- answer;
//  funcptr func;
// This type must be called Integration

typedef struct
{
	double upperlimit;
	double lowerlimit;
	int intervals;
	double answer;
	funcptr func;
  // ?????
} Integration;

// two functions to be implemented
void integrate(Integration * intrg);
bool runIntegrate(char * infilename, char * outfilename);
#endif
