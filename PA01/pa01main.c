// * DO NOT MODIFY THIS FILE * 
// If you modify this file, your program may be incompatible
// in grading and you may lose points.
// 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pa01.h"

// --------------------------------------------------------------
// < > for including header files from C language and library
// " "   for  including header files in this directory

// return true if the order is ascending
// return false if any adjacent elements are out of order
// A static function can be called only within the same file
// A static function is invisible outside this file
static bool checkArrayAscending(int * arr, int size)
{
  for (int ind = 0; ind < (size -1); ind ++) // remember -1
    {
      if (arr[ind] > arr[ind + 1])
	{
	  return false;
	}
    }
#ifdef DEBUG
  printf("arr is in ascending order\n");
#endif
  return true;
}

// --------------------------------------------------------------
// create a type of functions. The function returns nothing (void) and
// takes two input arguments. The first is an integer pointer as the
// starting address of an array. The second is the size of the array
typedef void (* sortFunction)(int * arr, int size);

// return true if the array sorted in the ascending order
// return false when encountering any problem
// func is the sorting function to run
// filename is the name of the file where the data is stored
static bool  testSort(sortFunction func, char * filename)
{
  FILE * fptr = fopen(filename, "r");
   if (fptr == NULL)
    {
      fprintf(stderr, "fopen fail\n");
      return false;
    }
   int rtv; // return value
   // go to the end of the file
   rtv = fseek(fptr, 0, SEEK_END);
   if (rtv == -1)
     {
       fprintf(stderr, "fseek fail\n");
       fclose(fptr);
       return false;
     }
   long floc = ftell(fptr);
   // calculate the number of elements in the file
   int numelem = (int) floc / sizeof(int);
#ifdef DEBUG
   printf("%d elements\n", numelem);
#endif

   // allocate memory
   int * arr = malloc(sizeof(* arr) * numelem);
   if (arr == NULL)
     {
       fprintf(stderr, "malloc arr fail\n");
       fclose(fptr);
       return false;
     }

   // return to the beginning of the file
   // do not use rewind because rewind does not report failure
   rtv = fseek(fptr, 0, SEEK_SET);
   if (rtv == -1)
     {
       fprintf(stderr, "fseek fail\n");
       fclose(fptr);
       free (arr);
       return false;
     }
   // read the array's values
   rtv = fread(arr, sizeof(* arr), numelem, fptr);
   if (rtv != numelem)
     {
       fprintf(stderr, "fread fail\n");
       fclose(fptr);
       free (arr);
       return false;
     }
   fclose (fptr);

#ifdef DEBUG
   printArray(arr, numelem);
#endif

   func(arr, numelem);

#ifdef DEBUG
   printArray(arr, numelem);
#endif

   bool sorted = checkArrayAscending(arr, numelem);
   free (arr);
   if (sorted == false)
     {
       return false;
     }
   return true;
}

// --------------------------------------------------------------
int main(int argc, char * * argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "need the name of an input file\n");
      return EXIT_FAILURE;
    }
   // test selection sort
#ifdef SELECTION_SORT
  if (testSort(selectSort, argv[1]) == false)
    {
      fprintf(stderr, "selectSort fail\n");
      return EXIT_FAILURE;
    }
#endif

#ifdef QUICK_SORT
  if (testSort(quickSort, argv[1]) == false)
    {
      fprintf(stderr, "quickSort fail\n");
      return EXIT_FAILURE;
    }
#endif

  return EXIT_SUCCESS;
}
