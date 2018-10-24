#ifndef _EXPRESSIONTREE_H
#define _EXPRESSIONTREE_H

#include "tree.h"
#include "scanner.h"

/* Build an expression tree from the infix expression scanned in by the    
   Scanner * s. See README for details.

   Arguments:
   Scanner * s: A scanner initialized with an input file containing an infix
                expression.

   Return: A pointer to the root of the generated expression tree.
*/
TreeNode * buildExpressionTree(Scanner * s);

/* Output the postfix form of an expression tree.

   Arguments:
   TreeNode * t: The root of a tree capturing an expression
   FILE * fptr: The file handle to output the postfix expression to

   Return: void
*/
void makePostFix(TreeNode * t, FILE * fptr);

#endif