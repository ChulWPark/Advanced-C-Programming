#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "path.h"

int main(int argc, char ** argv) {
	if (argc != 3) {
		fprintf(stderr, "Wrong number of command line args\n");
		fprintf(stderr, "Usage: ./pa07 mazeFile pathFile\n");
		return EXIT_FAILURE;
	}
	
	Maze * m = readMaze(argv[1]);
	if (m == NULL) {
		return EXIT_FAILURE;
	}
	
	char * path = readPath(argv[2]);
	if (path == NULL) {
		freeMaze(m);
		free(m);
		return EXIT_FAILURE;
	}
	
	if (checkPath(m, path)) {
		printf("Success!\n");
	} else {
		printf("Failure!\n");
	}
	
	//Clean up memory
	freeMaze(m);
	free(m);
	free(path);
	
	return EXIT_SUCCESS;
}
