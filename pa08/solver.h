#ifndef _SOLVER_H_
#define _SOLVER_H_
#include "maze.h"

char * solveMaze(Maze * m);

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step);

#endif
