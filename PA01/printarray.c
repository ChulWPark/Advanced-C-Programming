// * DO NOT MODIFY THIS FILE * 
// If you modify this file, your program may be incompatible
// in grading and you may lose points.
// 
#include <stdio.h>
#include "pa01.h"

void printArray(int * arr, int size)
{
  for (int ind = 0; ind < size; ind ++)
    {
      printf("arr[%d] = %d\n", ind, arr[ind]);
    }
  printf("\n\n");
}
