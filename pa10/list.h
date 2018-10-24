#ifndef _PATHS_H_
#define _PATHS_H_

//Linked list node
typedef struct PathNode {
	char * path;
	struct PathNode * next;
} PathNode;

//Structure to hold head pointer of linked list
typedef struct PathLL {
	PathNode * head;
} PathLL;

//Allocate and initialize an empty Path linked list
PathLL * buildPaths();

//Remove all nodes from a linked list, deallocate the PathLL structure
void freePaths(PathLL * p);

//Allocate a new PathNode with path as its data, return the address
PathNode * buildNode(char * path);

//Deallocate a pathNode
void freeNode(PathNode * p);

/*Add a path to the list of paths
  PathLL should be sorted by the following priority
  1. In ascending order of length (shortest path first), then
  2. By number of turns (see README), then
  3. Alphabetical order
 
  return true if the node is added successfully 
*/
bool addNode(PathLL * paths, char * path);

bool compareNode(PathNode * node1, PathNode * node2);
/*Remove a node from the list with the specified path

  return true if the node exists and is removed, false otherwise
*/
bool removeNode(PathLL * paths, char * path);

/* Return true if path exists in the list */
bool containsNode(PathLL * paths, char * path);

/* Write the paths in the list, in order, one per line, to fptr*/
void printPaths(PathLL * paths, FILE * fptr);

#endif
