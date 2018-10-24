#include <stdio.h>
#include <stdbool.h>
#include "pa04.h"

// must enclose the function by #ifdef TEST_INTEGRATE 
// and #endif to enable partial credits
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  // integrate the function stored in intrg's func
  // store the result in intrg's answer

	int i;
	double sum;
	double gapUpLow = ((*intrg).upperlimit - (*intrg).lowerlimit) / (*intrg).intervals;

	for(i = 0; i < (*intrg).intervals; i++)
	{
		sum += (*intrg).func((*intrg).lowerlimit + (i * gapUpLow));
	}

	(*intrg).answer = (gapUpLow * sum);

}
 #endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE
// and #endif to enable partial credits

#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
// return true if it can successfully open and read the input 
// and open and write the output
// return false when encountering any problem
{
  // open the input file name for reading

	FILE *fd1 = fopen(infilename, "r");

  // if fopen fails, return false

	if(fd1 == NULL)
	{
		return false;
	}

  // read one double from the input file and store it in 
  // intrg's lowerlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false

	Integration itg1;
	
	int check = fscanf(fd1, "%lf", &itg1.lowerlimit);

	if(check != 1)
	{
		fclose(fd1);
		return false;
	}


  // read one double from the input file and store it in 
  // intrg's upperlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false

	check = fscanf(fd1, "%lf", &itg1.upperlimit);

	if(check != 1)
	{
		fclose(fd1);

		return false;
	}


  // read one int from the input file and store it in 
  // intrg's intervals
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false

	check = fscanf(fd1, "%d", &itg1.intervals);

	if(check != 1)
	{
		fclose(fd1);
		return false;
	}


  // close the input file

	fclose(fd1);


  // open the output file for writing
  // if fopen fails, return false

	FILE *fd2 = fopen(outfilename, "w");

	if(fd2 == NULL)
	{
		return false;
	}


  // create an array of funcptr called funcs with five elements:
  // func1, func2, ..., func5

	funcptr funcs[5] = {func1, func2, func3, func4, func5};


  // go through the elements in funcs 
  // for each element, call integrate for that function
  // write the result (stored in intrg's answer to 
  // the output file. each answer occupies one line (add "\n")
  // use fprintf

	int loop;

	for(loop = 0; loop < 5; loop++)
	{
		itg1.func = funcs[loop];
		integrate(&itg1);
	    // check the return value of fprintf. 
	    // If it is less one one, close the output
	    // file and return false

		if(fprintf(fd2, "%lf\n", itg1.answer) < 1)
		{
			return false;	
		}
	}



  // after going through all functions in funcs
  // close the output file

	fclose(fd2);


  // if the function reaches here, return true

	return true;

}
#endif // RUN_INTEGRATE
