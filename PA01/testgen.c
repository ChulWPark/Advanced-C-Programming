// * DO NOT MODIFY THIS FILE * 
// If you modify this file, your program may be incompatible
// in grading and you may lose points.
// 
// This program generates cases for testing sorting programs.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// return true if successful
// return false if fail
bool createTest(int size, char * filename)
{
  FILE * fptr = fopen(filename, "w");
  if (fptr == NULL)
    {
      return false;
    }
  if (size == 0)
    {
      fclose(fptr);
      return true;
    }
  // allocate an array
  int * arr = malloc(sizeof(* arr) * size);
  if (arr == NULL) // malloc fail
    {
      fclose (fptr);
      return false;
    }
  for (int ind = 0; ind < size; ind ++)
    {
      arr[ind] = rand();
      arr[ind] -= RAND_MAX /3; // make some negative
    }
  int rtv; // return value
  rtv = fwrite(arr, sizeof(* arr), size, fptr);
  // need to free and fclose regardless whether fwrite succeeds
  free (arr); 
  fclose(fptr);
  if (rtv != size) // fwrite fail
    {
      return false;
    }
  // fwrite succeed
  return true;
}

int main(int argc, char * * argv)
{
  srand(time(NULL));
  // the sizes of the test cases
  int sizes[] = {0, 1, 5, 13, 41, 97, 1021, 16383, 65533, 262143, 1048573};
  int numelem = sizeof(sizes) / sizeof(* sizes);
  char filename[80];
  for (int ind = 0; ind < numelem; ind ++)
    {
      sprintf(filename, "input%0d", sizes[ind]);
      bool rtv = createTest(sizes[ind], filename);
      if (rtv == false)
	{
	  fprintf(stderr, "createTest fail\n");
	  return EXIT_FAILURE;
	}
    }
  return EXIT_SUCCESS;
}
