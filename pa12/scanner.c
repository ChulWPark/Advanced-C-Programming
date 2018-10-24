#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

static bool isEOF(char la) {
	return ((la == '\0') || (la == '\n'));
}

static bool isOp(char la) {
	return ((la == T_ADD) ||
	    (la == T_SUB) ||
	    (la == T_DIV) ||
			(la == T_MUL));
}

static bool isLParen(char la) {
	return (la == T_LPAREN);
}

static bool isRParen(char la) {
	return (la == T_RPAREN);
}

static bool isDigit(char la) {
	return (((la >= '0') && (la <= '9')) || (la == '.'));
}

static bool isNegNum(char la, char la2) {
	return ((la == T_SUB) && isDigit(la2));
}

Scanner * scannerInit(char * filename) {
	
	FILE * fin = fopen(filename, "r");
	if (fin == NULL) return false;
	
	if (fseek(fin, 0L, SEEK_END)) {//move pointer to end of file
		fclose(fin);
		return NULL;
	}
	
	long length = ftell(fin); //length of input
	
	if (fseek(fin, 0L, SEEK_SET)) {//move pointer back to beginning
		fclose(fin);
		return NULL;
	}
	
	Scanner * retval = malloc(sizeof(Scanner));
	retval->buf = malloc((length + 1) * sizeof(char));
	
	fgets(retval->buf, length + 1, fin); //read string into buffer
	
	retval->pos = 0;
	
	fclose(fin);
	
	return retval;
}

void scannerClose(Scanner * s) {
	free(s->buf);
	free(s);
}

Token nextToken(Scanner * s) {
	
	char la = s->buf[s->pos];
	char la2 = s->buf[s->pos + 1];
	
	// fprintf(stderr, "lookahead char: %c, pos: %d", la, pos);
	
	//Eat whitespace
	while (la == ' ') {
		s->pos++;
		la = la2;
		la2 = s->buf[s->pos + 1];
	}
	
	//If it's an op or a paren, eat the character and return the op type
	if (!isNegNum(la, la2) && (isOp(la) || isLParen(la) || isRParen(la))) {
		s->pos++;
		Token t = {.type = la};
		return t;
	}
	
	//If it's the end of the input, return T_EOF
	if (isEOF(la)) {
		Token t = {.type = T_EOF};
		return t;
	}
	
	//It should be an integer at this point:
	if (!isDigit(la) && !isNegNum(la, la2)) {
		fprintf(stderr, "Weird input at position %d [%c %c]\n", s->pos, la, la2);
		exit(1);
	}
	
	//If it's a numerical value, read a float from the input
	char tokbuf[15];
	int tokbufpos = 0;
	bool sawDec = false;
	
	if (isNegNum(la, la2)) {
		tokbuf[0] = '-';
		tokbufpos++;
		s->pos++;
		la = s->buf[s->pos];
	}
	
	while (isDigit(la)) {
		// fprintf(stderr, "character: %c @ %d\n", la, pos);
		if (la == '.') {
			if (!sawDec) {
				sawDec = true;
			} else {
				fprintf(stderr, "Weird input -- too many decimal points -- at position %d\n", s->pos);
				exit(1);
			}
		}
		tokbuf[tokbufpos++] = s->buf[s->pos++];
		
		la = s->buf[s->pos];
	}
	tokbuf[tokbufpos] = '\0';
	
	Token t = {.type = T_VAL, .value = atof(tokbuf)};
	
	return t;
}

void printToken(Token t, FILE * fout) {
	fprintf(fout, "Token type: ");
	switch (t.type) {
		case T_VAL: fprintf(fout, "VAL = %f", t.value); break;
		case T_ADD: fprintf(fout, "OP: +"); break;
		case T_SUB: fprintf(fout, "OP: -"); break;
		case T_MUL: fprintf(fout, "OP: *"); break;
		case T_DIV: fprintf(fout, "OP: /"); break;
		case T_LPAREN: fprintf(fout, "LPAREN"); break;
		case T_RPAREN: fprintf(fout, "RPAREN"); break;
		case T_EOF: fprintf(fout, "EOF"); break;
		default: fprintf(fout, "ERROR!\n"); exit(1);
	}
	fprintf(fout, "\n");
}
