#include "msort.h"
#include "student.h"
#include <stdio.h>

#ifndef OMIT_MSORT
void msort(Student * base, int nel, int (*compar)(const void *, const void *)) {
	
	//Base case: if the array has one or fewer elements, it's already sorted
	//so just return.
	
	if ( nel <= 1 )
	{
		return;
	}
	//FILL IN
	
	//Inductive case: split the array in two, sort the two pieces with msort,
	//merge the	sorted pieces
	
	//We're going to do this without explicitly creating the two separate arrays
	//We'll take advantage of the fact that to C, an array is just a pointer to
	//a region of memory. If we call msort on base, but pass in a smaller number
	//of elements, it will sort just that subarray. Similarly, if we call msort
	//but pass in the address of an element in the middle of the array, it will
	//sort the array *starting* from that element.
		
	//1. Find the midpoint of the array
	
	int half = nel / 2;
	//FILL IN
	
	//2a. Sort the first half of the array (remember to adjust the # elements)
	
	msort( base, half, compar );
	//FILL IN
	
	//2b. Sort the second half of the array. Pass in the address of the 
	//beginning of the second half of the array (remember to use the right # of 
	//elements)

	msort( base + half, nel - half, compar );
	//FILL IN
	
	//3a. Merge the two arrays (use merge)

	Student * arr_return = merge( base, half, base + half, nel - half , compar );  
	//FILL IN
	
	//3b. Copy the merged array over top of the original array (use copy)
	//Don't forget to free the array you no longer need!
	
	copy( base, arr_return, nel );

	free( arr_return );
	//FILL IN
		
	return;
}
#endif

#ifndef OMIT_MERGE
Student * merge(Student * base1, int nel1, Student * base2, int nel2, int (*compar)(const void *, const void *)) {
	
	//1. Allocate space for the returned merged array
	
	Student * arr_return = malloc( sizeof(Student) * ( nel1 + nel2 ) );
	//FILL IN
	
	//2. Create indices to keep track of where you are in the three arrays
	
	int base1index = 0;
	int base2index = 0;
	int returnindex = 0;
	//FILL IN
	
	//3. Go through base1 and base2, and merge them into the returned array
	
	while( ( base1index < nel1 ) && ( base2index < nel2 ) )
	{
		if( compar( &base1[base1index], &base2[base2index] ) > 0 )
		{
			arr_return[returnindex++] = base2[base2index++];
		}
		else
		{
			arr_return[returnindex++] = base1[base1index++];
		}
	}

	while( ( base1index < nel1 ) )
	{
		arr_return[returnindex++] = base1[base1index++];
	}

	while( ( base2index < nel2 ) )
	{
		arr_return[returnindex++] = base2[base2index++];
	}
	//FILL IN
	
	//4. Return the merged array
	
	return arr_return;
	//FILL IN

}


void copy(Student * to, Student * from, int nel) {
	/*
	An efficient implementation of this would use memcpy:
	memcpy(to, from, nel * width);

	We will do an element-by-element copy so you can see how it is done
	*/
	
	//loop over the from array and copy it byte by byte to the to array.
	for (int i = 0; i < nel; i++) {
		to[i] = from[i];
	}
	
	return;
}
#endif
