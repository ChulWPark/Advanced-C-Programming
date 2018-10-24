#ifdef SELECTION_SORT
#include "pa01.h"
void selectSort(int * arr, int size)
//arr : the array to be sorted
//size : the number of elements in the array

// In each iteration, the number of elements to be sorted shrinks by one
// i.e., one element is at the correct position.
//
// Among the remaining elements, find the smallest value and put it 
// before the other unsorted elements
{
    int i;	//count variable for the first for loop
	int ii;	//count variable for the second for loop
	int comparestart;	//index for the first number to be compared with the target
	int smallestvaluelocation;	//index location for the current smallest value
	int smallestvalue;	//numerical value of the current smallest value

	for((i = 0); (i < size -1); (i++))	//first for loop (target index that would be sorted)
	{
		comparestart = i + 1;
		smallestvaluelocation = i;
		for((ii = comparestart); (ii < size); (ii++))	//second for loop (compare with the unsorted numbers and find the smallest value)
		{
			if(arr[ii] < arr[smallestvaluelocation])
			{
				smallestvaluelocation = ii;
				smallestvalue = arr[ii];
			}
		}
		//SWAP
		arr[smallestvaluelocation] = arr[i];
		arr[i] = smallestvalue;
	}

	//TODO: Fill this in to complete PA01.

}
#endif
