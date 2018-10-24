#ifndef _MAZEHELPER_H_
#define _MAZEHELPER_H_
#include "maze.h"

bool atEnd(MazePos cur, Maze * m);

bool inBounds(MazePos cur, Maze * m);

bool hitWall(MazePos cur, Maze * m);

bool isVisited(MazePos cur, Maze * m);

bool squareOK(MazePos cur, Maze * m);

#endif
