#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

#ifndef READMAZE_OFF
Maze * readMaze(char * mazeFilename) {
	FILE * inMaze = fopen(mazeFilename, "r");

	if (inMaze == NULL) {
		fprintf(stderr, "Could not open maze file for reading\n");
		exit(1);
	}
		
	//Allocate Maze structure
	Maze * m = malloc(sizeof(Maze));
		
	//Read in the dimensions of the maze
	if (fscanf(inMaze, "%d %d\n", &(m->height), &(m->width)) != 2) {
		fprintf(stderr, "Malfored input: can't get maze dimensions\n");
		free(m);
		return NULL;
	}
	
	//Allocate the 2D array in m
	m->maze = malloc(m->height * sizeof(MazeSquare *));
	for (int i = 0; i < m->width; i++) {
		m->maze[i] = malloc(m->width * sizeof(MazeSquare));
	}
	
	//Read in the maze -- assume that it is well formatted
	for (int i = 0; i < m->height; i++) {
		for (int j = 0; j < m->width; j++) {
			int val = fgetc(inMaze);

			m->maze[i][j].type = val;
			m->maze[i][j].visited = false;

			if (val == END) {
				m->end.xpos = j;
				m->end.ypos = i;
			} else if (val == START) {
				m->start.xpos = j;
				m->start.ypos = i;
			}
		}
		//consume extra \n
		int c = fgetc(inMaze);
		//Error check: c had better be a \n:
		if (c != '\n') {
			fprintf(stderr, "Malformed input\n");
			freeMaze(m);
			free(m);
			return NULL;
		}
	}
	
	//close the file
	if (fclose(inMaze)) {
		fprintf(stderr, "Error closing file\n");
		freeMaze(m);
		free(m);
		return NULL;
	}
	
	return m;
}
#endif //#ifndef READMAZE_OFF

#ifndef FREEMAZE_OFF
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
	for (int i = 0; i < m->height; i++) {
		free(m->maze[i]);
	}
	
	//2. Free the "spine" of the array
	free(m->maze);
}
#endif //#ifndef FREEMAZE_OFF
