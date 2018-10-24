#ifndef _CALC_H_
#define _CALC_H_
#include<stdbool.h>

//Linked list node
typedef struct CalcNode{
	float element;
	struct CalcNode * next;
}CalcNode;

//Structure to hold head pointer of linked list
typedef struct CalcLL{
	CalcNode * head;
}CalcLL;

//Allocate and initialize an empty calc linked list
CalcLL * buildCalc();

//remove all nodes from a linked list, deallocate the calcLL structure
void freeCalc(CalcLL * p);

//Allocate a new calcNode with element as its data, return the address
CalcNode * buildNode(float element);

//Push an element to the list of elements
bool pushelem(CalcLL * p, float element);

//Pop an element out of the list of elements
bool popelem(CalcLL * p);

//Print the elements in the list to the command window
void printElements(CalcLL * p);

#endif
