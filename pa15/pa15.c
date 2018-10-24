#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
	long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
	if (asciiCount == NULL) {
		return NULL;
	}
	int ch;
	for (ch = 0; ch < ASCII_SIZE; ch++) {
		asciiCount[ch] = 0;
	}
	fseek(fp, 0, SEEK_SET);
	while ((ch = fgetc(fp)) != EOF) {
		asciiCount[ch] += 1;
	}
	return asciiCount;
}

int main(int argc, char **argv)
{
	if (argc != 5) {
	printf("Not enough arguments");
	return EXIT_FAILURE;
	}
	FILE * inFile = fopen(argv[1], "r");
	if (inFile == NULL) {
		fprintf(stderr, "can't open the input file.  Quit.\n");
		return EXIT_FAILURE;
	}

	/* read and count the occurrences of characters */
	long *asciiCount = countLetters(inFile);
	fclose(inFile);

	if (asciiCount == NULL) {
		fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
		return EXIT_FAILURE;
	} 
	
	// Your code should go here
	ListNode * head = NULL;
	
	///////////////////_sorted//////////////////////////////////
	FILE * sortedFile = fopen(argv[2], "w");
	if (sortedFile == NULL) {
		fprintf(stderr, "can't open the sorted file.  Quit.\n");
		return EXIT_FAILURE;
	}
	////////////////////sorted linked list//////////////////////
	int i = 0;
	for(i = 0; i < ASCII_SIZE; i++)
	{
		if(asciiCount[i] != 0)
		{
			head = addNode(head,i,asciiCount[i]);
		}
	}
	ListNode * curnode = head;
	while(curnode != NULL)
	{
		fprintf(sortedFile,"%c:%ld\n",curnode->ptr->label,curnode->ptr->count);
		curnode = curnode->next;
	}
	fclose(sortedFile);
	////////////////////////////////////////////////////////////
	
	//////////////////Create Huffman Tree///////////////////////
	ListNode * namu = buildTree(head);
	///////////////////_huffman/////////////////////////////////
	FILE * huffmanFile = fopen(argv[3], "w");
	if (huffmanFile == NULL) {
		fprintf(stderr, "can't open the sorted file.  Quit.\n");
		return EXIT_FAILURE;
	}
	char * huff = malloc(sizeof(char) * 10000000);
	int * index = malloc(sizeof(int));
	index[0] = 0;
	printTree(namu->ptr, huffmanFile, huff, index);
	free(huff);
	free(index);
	fclose(huffmanFile);	
	////////////////////////////////////////////////////////////
	
	//////////////////_header///////////////////////////////////
	FILE * headerFile = fopen(argv[4], "w");
	if (headerFile == NULL) {
		fprintf(stderr, "can't open the sorted file.  Quit.\n");
		return EXIT_FAILURE;
	}
	unsigned char temp1 = 0;
	unsigned char temp2 = 0;
	unsigned char * whichbit = &temp1;
	unsigned char * curbyte = &temp2;
	printHeader(namu->ptr, headerFile, whichbit, curbyte);
	fclose(headerFile);
	////////////////////////////////////////////////////////////
	
	/////////////////////FREE///////////////////////////////////
	free(asciiCount);	
	freeTree(namu->ptr);
	free(namu);
	////////////////////////////////////////////////////////////
	
	return EXIT_SUCCESS;
}
