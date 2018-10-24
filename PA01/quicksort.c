#ifdef QUICK_SORT
#include <stdio.h>
#include <stdlib.h>
#include "pa01.h"
static void quickSortHelp(int * arr, int first, int last)
{
  if (first >= last) // no need to sort one or no element 
    {
      return; 
    }
#ifdef DEBUG
  printf("first = %d, last = %d\n", first, last);
#endif 
  int pivot = arr[first];
  int low = first + 1;
  int high = last;
  while (low < high)
    {
      while ((low < last) && (arr[low] <= pivot))
	{
	  // <= so that low will increment when arr[low] 
	  // is the same as pivot,  using < will stop 
	  // incrementing low when arr[low] is the same 
	  // as pivot and the outer while loop will not stop
	  low ++;
	}
      while ((first < high) && (arr[high] > pivot))
	{
	  high --;
	}
      if (low < high)
	{
	  swap (& arr[low], & arr[high]);
	}
    }
  if (pivot > arr[high])
    {
      swap(& arr[first], & arr[high]);
    }
  quickSortHelp(arr, first, high - 1);
  quickSortHelp(arr, low, last);
}
void quickSort(int * arr, int len)
{
  quickSortHelp(arr, 0, len - 1);
}
#endif
