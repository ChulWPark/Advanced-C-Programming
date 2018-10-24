#ifndef _PATH_H_
#define _PATH_H_

#include <stdbool.h>
#include "maze.h"

//Enum for path type
typedef enum PathType {
	NORTH = 'n',
	SOUTH = 's',
	EAST = 'e',
	WEST = 'w'
} PathType;

/*
Read in a string containing the path from file. Return the string. Be sure
that the string ends with a null-terminating character!

Arguments:
pathFilename: name of the file containing the path

Return:
NULL if readPath fails for any reason
Pointer to character array containing path string otherwise.
*/
char * readPath(char * pathFilename);

/*
Write a string containing a path to a file.

Arguments:
pathFilename: name of the file to output the path to
path: string containing path

Return:
0 if successful
1 otherwise.
*/
int writePath(char * pathFilename, char * path);

/*
Check path, return true if path hits exit, false if path loops or hits a wall

The path string is formatted as a sequence of characters: 'n' for north (move
up), 's' for south (move down), 'e' for east (move right), 'w' for west (move
left). Don't forget that in 2D array coordinates, moving *up* means
*decrementing* the row you are at, and moving *down* means *incrementing* the
row you are at.
*/
bool checkPath(Maze * m, char * path);

#endif
