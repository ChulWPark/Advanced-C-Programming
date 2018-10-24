#include <stdio.h>
#include <stdlib.h>
#include "path.h"

#ifndef READPATH_OFF
char * readPath(char * pathFilename)
{
    FILE * pathdata = fopen(pathFilename, "r");
    
    if(pathdata == NULL)
    {
        return NULL;
    }
    
	//COUNT the number of characters
    int count = 0;
    while( fgetc(pathdata) != EOF)
    {
        count++;
    }
    count = count - 1;
    
	//print number of characters
	//printf("\nNumber of characters = %d\n", count);
	
	//move to the beginning of the file
    fseek(pathdata, 0, SEEK_SET);
    
	//create a string for path
    char* pathorder = malloc(sizeof(char) * (count + 1) );
    pathorder[count] = '\0';
	
	//Put the data into the string
    int i = 0;
    while( i < count )
    {
        fscanf(pathdata, "%c", &pathorder[i]);
        i++;
    }
    
	//print path string
	/*printf("\n--------PATH STRING---------\n");
	for(i = 0; i < count; i++)
	{
		printf("%c", pathorder[i]);
	}
	printf("\n---------------------\n\n");
    */

    fclose(pathdata);
    
    return pathorder;
}
#endif //#ifndef READPATH_OFF

#ifndef CHECKPATH_OFF
bool checkPath(Maze * m, char * path)
{
    // Get Length of the path array
    int lenPath = 0;

	while(path[lenPath] != '\0')
    {
        lenPath++;
    } 
   	
    // LOOP
    int i = 0;
    
    for(i = 0; i <= lenPath; i++)
    {
        if( path[i] == 'e' )
        {
            if( (m->start.xpos + 1) > (m->width - 1) )
            {
                return false;
            }
            
            if(m->maze[m->start.ypos][m->start.xpos + 1].type == (SquareType) SPACE)
            {
                m->maze[m->start.ypos][m->start.xpos].visited = true;
				m->start.xpos++;
				if(m->maze[m->start.ypos][m->start.xpos].visited == true)
				{
					return false;
				}
            }
            else if(m->maze[m->start.ypos][m->start.xpos + 1].type == (SquareType) END)
            {   
                return true;
            }
            else
            {   
                return false;
            }
        }// e
        
		else if( path[i] == 'w' )
        {
            if( (m->start.xpos - 1) < 0 )
            {
                return false;
            }
            
            if(m->maze[m->start.ypos][m->start.xpos - 1].type == (SquareType) SPACE)
            {
                m->maze[m->start.ypos][m->start.xpos].visited = true;
				m->start.xpos--;
				if(m->maze[m->start.ypos][m->start.xpos].visited == true)
				{
					return false;
				}
            }
            else if(m->maze[m->start.ypos][m->start.xpos - 1].type == (SquareType) END)
            {   
                return true;
            }
            else
            {   
                return false;
            }
        }// w
        
		else if( path[i] == 's' )
        {
            if( (m->start.ypos + 1) > (m->height - 1) )
            {
                return false;
            }
            
            if(m->maze[m->start.ypos + 1][m->start.xpos].type == (SquareType) SPACE)
            {
				m->maze[m->start.ypos][m->start.xpos].visited = true;
                m->start.ypos++;
				if(m->maze[m->start.ypos][m->start.xpos].visited == true)
				{
					return false;
				}
            }
            else if(m->maze[m->start.ypos + 1][m->start.xpos].type == (SquareType) END)
            {            
                return true;
            }
            else
            {
                return false;
            }
        }// s
        
		else if( path[i] == 'n')
        {
            if( (m->start.ypos - 1) < 0 )
            {
                return false;
            }
            
			if(m->maze[m->start.ypos - 1][m->start.xpos].type == (SquareType) SPACE)
            {
				m->maze[m->start.ypos][m->start.xpos].visited = true;
                m->start.ypos--;
				if(m->maze[m->start.ypos][m->start.xpos].visited == true)
				{
					return false;
				}
            }
            else if(m->maze[m->start.ypos - 1][m->start.xpos].type == (SquareType) END)
            {
                return true;
            }
            else
            {
                return false;
            }
        }// n
        
		else
		{
			return false;
		}
    }
    
	return false;
}
#endif //#ifndef CHECKPATH_OFF
