#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"
#include "scanner.h"

#ifndef BUILDTREE_OFF
TreeNode * buildExpressionTree(Scanner * s) {
//FILL IN
	TreeNode * leftchild;
	TreeNode * rightchild;
	Token op;
	char temp[100000];
	int index = 0;
	
	//IF IT IS LPAREN
	if(s->buf[s->pos] == '(')
	{
		s->pos++;
		leftchild = buildExpressionTree(s); //RECURSION
		s->pos += 2;
	}
	//IF IT IS NUMBER OR '.' OR '-'
	if( (s->buf[s->pos] >= '0' && s->buf[s->pos] <= '9') || s->buf[s->pos] == '.' || s->buf[s->pos] == '-')
	{
		if(s->buf[s->pos] == '-' && s->buf[s->pos + 1] == ' ')
		{
			//IF IT IS OPERATOR, MOVE ON (IT WILL GET CAUGHT IN NEXT IF STATEMENT)
		}
		else
		{
			Token t;
			t.type = T_VAL;
			index = 0;
			while(s->buf[s->pos] != ' ' && s->buf[s->pos] != ')')
			{
				temp[index] = s->buf[s->pos];
				s->pos++;
				index++;
			}
			temp[index] = '\0';
			t.value = atof(temp);
			s->pos--;
			TreeNode * returnnode = buildTreeNode(t);
	
			return returnnode;
		}
	}
	//IF IT IS OPERATOR
	if(s->buf[s->pos] == '+' || s->buf[s->pos] == '-' || s->buf[s->pos] == '*' || s->buf[s->pos] == '/')
	{
		if(s->buf[s->pos] == '+')
		{
			op.type = T_ADD;
			s->pos += 2;
			rightchild = buildExpressionTree(s);
			s->pos++;
		}
		else if(s->buf[s->pos] == '-')
		{
			op.type = T_SUB;
			s->pos += 2;
			rightchild = buildExpressionTree(s);
			s->pos++;
		}
		else if(s->buf[s->pos] == '*')
		{
			op.type = T_MUL;
			s->pos += 2;
			rightchild = buildExpressionTree(s);
			s->pos++;
		}

		else if(s->buf[s->pos] == '/')
		{
			op.type = T_DIV;
			s->pos += 2;
			rightchild = buildExpressionTree(s);
			s->pos++;
		}
	}
	//IF IT IS RPAREN
	if(s->buf[s->pos] == ')')
	{
		TreeNode * opmom = buildTreeNode(op);
		opmom -> left = leftchild;
		opmom -> right = rightchild;
		return opmom;
	}
	
	return NULL;
}
#endif

#ifndef POSTFIX_OFF
void makePostFix(TreeNode * t, FILE * fptr) {
//FILL IN
	if(t == NULL)
	{
		return;
	}
	else if(t->t.type == T_ADD || t->t.type == T_SUB || t->t.type == T_MUL || t->t.type == T_DIV)
	{
		makePostFix(t->left, fptr);	//RECURSIVE CALL TO THE LEFT
		makePostFix(t->right, fptr);	//RECURSIVE CALL TO THE RIGHT
		fprintf(fptr, "%c ", t->t.type);
	}
	else if(t->t.type == T_VAL)
	{
		fprintf(fptr, "%f ", t->t.value);
		return;
	}

}
#endif
