// wrongindex2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void f1(int * arr)
{
  arr[-2]  = 2016;
}

int main(int argc, char * * argv)
{
  int x = -2;
  int arr[] = {0, 1, 2, 3, 4};
  int y = 15;
  printf("& x      = %p, & y      = %p\n", (void *) & x, (void *) & y);
  printf("& arr[0] = %p, & arr[4] = %p\n", 
	 (void *) & arr[0], (void *) & arr[4]);
  printf("x = %d, y = %d\n", x, y);
  f1(arr);
  printf("x = %d, y = %d\n", x, y);

  return EXIT_SUCCESS;
}
