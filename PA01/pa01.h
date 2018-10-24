// * DO NOT MODIFY THIS FILE * 
// If you modify this file, your program may be incompatible
// in grading and you may lose points.
// 
#ifndef PA01_H
#define PA01_H
// A header file always 
// starts with #ifndef ... #define 
// and ends with #endif
// Why is this necessary? To prevent multiple inclusion
// If a header file has already been included, it will
// not be included again.

// If you want to see the header files from the C language
// (such as stdio.h and stdlib.h),  you can find them at /usr/include

#ifdef SELECTION_SORT
void selectSort(int * arr, int size);
#endif

#ifdef QUICK_SORT
void quickSort(int * arr, int size);
#endif

void swap(int * a, int * b);

void printArray(int * arr, int size);

#endif
