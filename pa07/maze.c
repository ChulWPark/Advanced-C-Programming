#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

#ifndef READMAZE_OFF
Maze * readMaze(char * mazeFilename) {
	
	//open the maze file
	FILE * mazedata = fopen(mazeFilename, "r");
	if(mazedata == NULL)
	{
		return false;
	}
	
	//malloc "mazestruct", which is type Maze *
	Maze * mazestruct = malloc(sizeof(Maze));
	
	//copy the height and width of the 2D array
	fscanf(mazedata, "%d %d\n", &(*mazestruct).height, &(*mazestruct).width);
	
	//print height and width
	//printf("\nheight = %d, width = %d\n", mazestruct->height, mazestruct->width);

	//malloc "mazestruct->maze", which is 2D array
	mazestruct->maze = malloc( (*mazestruct).height * sizeof(MazeSquare *) );
	int row;
	for( row = 0; row < (*mazestruct).height; row++ )
	{
		mazestruct->maze[row] = malloc( (*mazestruct).width * sizeof(MazeSquare) );
	}
	
	//copy the contents of the mazefile and put them in the "mazestruct->maze", which is 2D array that I malloced
	int col;
	char *ch = malloc( sizeof(char) * (mazestruct->width + 1) );
	for(row = 0; row < (*mazestruct).height; row++)
	{
		fscanf(mazedata, "%s", ch);
		for(col = 0; col < (*mazestruct).width; col++)
		{
			if( ch[col] == '#' )
			{
				mazestruct->maze[row][col].type = WALL;	
			}
			else if( ch[col] == '.' )
			{
				mazestruct->maze[row][col].type = SPACE;
			}
			else if( ch[col] == 's' )	//set that location's type to START and also save that location's xpos and ypos
			{
				mazestruct->maze[row][col].type = START;
				mazestruct->start.xpos = col;
				mazestruct->start.ypos = row;
			}
			else if( ch[col] == 'e' )	//set that location's type to END and also save that location's xpos and ypos
			{
				mazestruct->maze[row][col].type = END;
				mazestruct->end.xpos = col;
				mazestruct->end.ypos = row;
			}
			//When the mazefile has a character other than (# . s e)
			//else
			//{
			//	return NULL;
			//}
				
		}
	}

	//initialize all .visited attribute to false since at the beginning no location is visited at all
	for(row = 0; row < mazestruct->height; row++)
	{
		for(col = 0; col < mazestruct->width; col++)
		{
			mazestruct->maze[row][col].visited = false;
		}
	}
	
	//print start point and end point
	//printf("\nstart[][]: %d %d\n", mazestruct->start.ypos, mazestruct->start.xpos);
	//printf("\nend[][]: %d %d\n", mazestruct->end.ypos, mazestruct->end.xpos);

	//print maze 2D array
	/*
	printf("------------MAZE-------------\n");
	for(i = 0; i < mazestruct->height; i++)
	{
		for(j = 0; j < mazestruct->width; j++)
		{
			printf("%c", mazestruct->maze[i][j].type);
		}
		printf("\n");
	}
	printf("\n");
	*/
	
	//free the string used to copy into the 2D array
	free(ch);
	
	//close the maze file
	fclose(mazedata);
	
	//return the type Maze * mazestruct (which is the root of the struct)
	return mazestruct;
}
#endif //#ifndef READMAZE_OFF

#ifndef FREEMAZE_OFF
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
	for (int row = 0; row < m->height; row++)
	{
		free(m->maze[row]);
	}
	//2. Free the "spine" of the array
	free(m->maze);
}
#endif //#ifndef FREEMAZE_OFF
