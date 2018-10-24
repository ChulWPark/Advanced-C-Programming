#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/
//ALREADY IMPLEMENTED
PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	PathNode* to_remove = p -> head;

	while(p -> head != NULL)
	{
		to_remove = p -> head;
		p -> head = p -> head -> next;
		freeNode(to_remove);
	}
	
	free(p);
}

PathNode * buildNode(char * path) {
	PathNode * nodemade = malloc(sizeof(PathNode));
	nodemade->path = malloc(strlen(path) + 1);
	strcpy(nodemade->path, path);
	nodemade -> next = NULL;
	return nodemade;
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
}

void freeNode(PathNode * p) {
	//fill in
	free(p->path);
	free(p);
}

bool addNode(PathLL * paths, char * path) {
	//fill in
	//IF PATH ALREADY EXITS, return false
	if(containsNode(paths,path))
	{
		return false;
	}
	
	//IF paths->head IS NULL, PUT THE PATH IN HEAD AND SET NEXT TO NULL AND return true
	if(paths -> head == NULL)
	{
		paths -> head = buildNode(path);
		paths -> head -> next = NULL;
		return true;
	}

	//IF paths->head IS NOT NULL
	else
	{
		PathNode * newnode = buildNode(path); //CREATE NEWNODE
		PathNode * curnode = paths -> head;	//CREATE CURSOR
		PathNode * prevnode = paths -> head;	//CREATE PREVIOUS CURSOR
		while(curnode != NULL)	//LOOP UNTIL IT HITS THE END OF THE LINKED LIST
		{
			if(compareNode(curnode, newnode)) //IF NEWNODE IS GREATER
			{
				prevnode = curnode;
				curnode = curnode -> next;
			}
			else //IF NEWNODE IS LESS
			{
				if( curnode == paths -> head ) 
				{
					newnode -> next = curnode;
					paths -> head = newnode;
					return true;
				}
				else
				{
					prevnode -> next = newnode;
					newnode -> next = curnode;
					return true;
				}
			}
		}
		prevnode -> next = newnode;
		newnode -> next = curnode;
		return true;
	}
}

bool compareNode(PathNode * node1, PathNode * node2)
{
	//LENGTH ORDER
	if(strlen(node1->path) < strlen(node2->path))
	{
		return true;
	}
	else if(strlen(node1->path) > strlen(node2->path))
	{
		return false;
	}
	else
	{
		//TURN ORDER
		int turn1 = 0;
		int turn2 = 0;
		int i = 0;
		for(i = 0; i < strlen(node1 -> path) - 1; i++)
		{
			if(node1->path[i] != node1->path[i + 1])
			{
				turn1++;
			}
		}
		for(i = 0; i < strlen(node2 -> path) - 1; i++)
		{
			if(node2->path[i] != node2->path[i + 1])
			{
				turn2++;
			}
		}
		if(turn1 < turn2)
		{
			return true;
		}
		else if(turn1 > turn2)
		{
			return false;
		}
		else
		{
			//ALPHABETICAL ORDER
			for(i = 0; i < strlen(node1 -> path); i++)
			{
				if( node1->path[i] < node2->path[i] )
				{
					return true;
				}
				else if( node1->path[i] > node2->path[i] )
				{
					return false;
				}
				else
				{
				}
			}
			return false;
		}
	}
}

bool removeNode(PathLL * paths, char * path) {
	//fill in
	PathNode * curnode = paths -> head;
	PathNode * target;
	if(strcmp(curnode -> path, path) == 0)
	{
		paths -> head = curnode -> next;
		freeNode(curnode);
		return true;
	}
	while(curnode != NULL)
	{
		if(curnode -> next != NULL)
		{
			if(strcmp(curnode -> next -> path, path) == 0)
			{
				target = curnode -> next;
				curnode -> next = target -> next;
				freeNode(target);
				return true;
			}
		}
		curnode = curnode -> next;
	}
	return false;
}

bool containsNode(PathLL * paths, char * path) {
	//fill in
	if(paths -> head == NULL)
	{
		return false;
	}
	else
	{
		PathNode * curnode = paths -> head;

		while(curnode -> next != NULL)
		{
			if(strcmp(curnode -> path, path) == 0)
			{
				return true;
			}
			curnode = curnode -> next;
		}
		
		if(strcmp(curnode -> path, path) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

//ALREADY IMPLEMENTED
void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
