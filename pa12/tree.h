#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include "scanner.h"

typedef struct TreeNode {
	Token t;
	struct TreeNode * left;
	struct TreeNode * right;
} TreeNode;

//Allocate a new TreeNode holding Token t, and return a pointer to it
TreeNode * buildTreeNode(Token t);

//De-allocate a TreeNode
void freeTreeNode(TreeNode * t);

//De-allocate an entire tree
void freeTree(TreeNode * t);

//Print the contents of the tree to the file specified by fptr
//Printing to stderr can be useful for debugging
void printTree(TreeNode * t, FILE * fptr);

#endif