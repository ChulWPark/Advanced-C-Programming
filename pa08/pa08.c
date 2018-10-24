#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "path.h"
#include "solver.h"

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of command line args\n");
        fprintf(stderr, "Usage: ./pa07 mazeFile\n");
        return EXIT_FAILURE;
    }   
    
    Maze * m = readMaze(argv[1]);
    if (m == NULL) {
        return EXIT_FAILURE;
    }   

    /*char * path = readPath(argv[2]);
    if (path == NULL) {
        freeMaze(m);
        free(m);
        return EXIT_FAILURE;
    }*/   
    
	char * path = solveMaze(m);
	
	/*
	int i = 0;
	printf("\n");
	while( path[i] != '\0' )
	{
		printf("%c", path[i]);
		i++;
	}
	printf("\n");
	*/

    //Clean up memory
    freeMaze(m);
    free(m);
    free(path);
    
    return EXIT_SUCCESS;
}

