#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "calc.h"

CalcLL * buildCalc(){
	CalcLL * retval = malloc(sizeof(CalcLL));
	retval -> head = NULL;
	return retval;
}

void freeCalc(CalcLL * p){
	CalcNode * to_remove = p -> head;

	while(p -> head != NULL)
	{
		to_remove = p -> head;
		p -> head = p -> head -> next;
		free(to_remove);
	}
	
	free(p);
}

CalcNode * buildNode(float element){
	CalcNode * nodemade = malloc(sizeof(CalcNode));
	nodemade -> element = element;
	return nodemade;
}

bool pushelem(CalcLL * p, float element){
	CalcNode * newnode = buildNode(element);
	
	if(p -> head == NULL)
	{
		p -> head = newnode;
		p -> head -> next = NULL;
		return true;
	}
	
	newnode -> next = p -> head;
	p -> head = newnode;
	return true;
}

bool popelem(CalcLL * p){
	CalcNode * curnode = p -> head;
	p -> head = p -> head -> next;
	free(curnode);
	return true;
}

void printElements(CalcLL * p){
	CalcNode * curnode = p -> head;
	while (curnode != NULL)
	{
		printf("%f", curnode->element);
		printf("\n");
		curnode = curnode -> next;
	}
	printf("\n");
}
