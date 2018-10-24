#include <stdio.h>
#include <stdlib.h>
#include "expressionTree.h"
#include "scanner.h"
#include "tree.h"

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf(stderr, "Error: wrong number of arguments\n");
		fprintf(stderr, "Usage: ./pa12 <input file> <output file>");
	}
	
	Scanner * s = scannerInit(argv[1]);
	
	if (s == NULL) {
		fprintf(stderr, "Error initializing scanner\n");
		exit(1);
	}
	
	TreeNode * et = buildExpressionTree(s);
	
	scannerClose(s);
	
	FILE * fptr = fopen(argv[2], "w");
	
	if (fptr == NULL) {
		fprintf(stderr, "Error opening output file for writing\n");
		freeTree(et);
		exit(1);
	} else {
		makePostFix(et, fptr);
		fprintf(fptr, "\n");
		freeTree(et);
		fclose(fptr);
	}
	
	return EXIT_SUCCESS;
}