#include "mazehelper.h"

bool atEnd(MazePos cur, Maze * m) {
	return (cur.xpos == m->end.xpos) && (cur.ypos == m->end.ypos);
}

bool inBounds(MazePos cur, Maze * m) {
	return ((cur.xpos >= 0) && cur.xpos < m->width) &&
		((cur.ypos >= 0) && cur.ypos < m->height);
}

bool hitWall(MazePos cur, Maze * m) {
	return m->maze[cur.ypos][cur.xpos].type == WALL;
}

bool isVisited(MazePos cur, Maze * m) {
	return m->maze[cur.ypos][cur.xpos].visited;
}

bool squareOK(MazePos cur, Maze * m) {
	return inBounds(cur, m) && !hitWall(cur, m) && !isVisited(cur, m);
}
