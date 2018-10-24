#include <stdlib.h>
#include "tree.h"

TreeNode * buildTreeNode(Token t) {
	TreeNode * ret = malloc(sizeof(TreeNode));
	ret->t = t;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

void freeTreeNode(TreeNode * t) {
	free(t);
}

void freeTree(TreeNode * t) {
	if (t == NULL) return;
	freeTree(t->left);
	freeTree(t->right);
	freeTreeNode(t);
}

static void printTreeHelper(TreeNode * t, int offset, FILE * fptr) {
	if (t == NULL) return;
	
	for (int i = 0; i < offset; i++) {
		fprintf(fptr, "  ");
	}
	printToken(t->t, fptr);
		
	printTreeHelper(t->left, offset + 1, fptr);
	printTreeHelper(t->right, offset + 1, fptr);
}

void printTree(TreeNode * t, FILE * fptr) {
	printTreeHelper(t, 0, fptr);
}