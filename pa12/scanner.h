#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdbool.h>
#include <stdio.h>

typedef enum TokenType {
	T_VAL = '@',    //This type is used to represent any number
	T_ADD = '+',    //This type is used to represent a +
	T_SUB = '-',    //This type is used to represent a -
	T_MUL = '*',    //This type is used to represent a *
	T_DIV = '/',    //This type is used to represent a /
	T_LPAREN = '(', //This type is used to represent a (
	T_RPAREN = ')', //This type is used to represent a )
	T_EOF = '!'     //This type represents the last token in the input
} TokenType;

typedef struct Token {
	TokenType type; //What type this token is
	float value;    //If type is T_VAL, this field contains the value of the 
					//number	
} Token;

typedef struct Scanner {
	char * buf;
	int pos;
} Scanner;

//return Scanner if scanner initialized and read in expression correctly
//return NULL otherwise
Scanner * scannerInit(char * filename);

//deallocate scanner
void scannerClose(Scanner * s);

//Return the next token in the input file that s was initializzed with
Token nextToken(Scanner * s);

//Print the current token to the specified file
//Printing to stderr can be useful for debugging
void printToken(Token t, FILE * fout);

#endif
