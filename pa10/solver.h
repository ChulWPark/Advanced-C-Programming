#ifndef _SOLVER_H_
#define _SOLVER_H_
#include "maze.h"
#include "list.h"

PathLL * solveMaze(Maze * m);

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths);

#endif
