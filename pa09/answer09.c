#include "answer09.h"

bool isCircular(const node_t * head)
{
	// INITIALIZE slowptr AND fastptr TO NULL (IT WON'T MATTER INITIALIZED TO WHICH VALUE BECAUSE IT'S GONNA BE REASSIGNED ANYWAY)
	node_t* slowptr = NULL;
	node_t* fastptr = NULL;
	
	// IF HEAD IS NULL, LINKED LIST DOESN'T EVEN EXIST, SO return false
	if( head == NULL )
	{
		return false;
	}
	
	// ASSIGN slowptr TO NEXT INDEX OF HEAD ONLY IF THAT IS NOT NULL
	if( head -> next )
	{
		slowptr = head -> next;
		
		if( head -> next -> next ) // ASSIGN fastptr TO NEXT NEXT INDEX OF HEAD ONLY IF THAT IS NOT NULL
		{
			fastptr = head -> next -> next;
		}
		else // IF NEXT NEXT INDEX OF HEAD IS NULL, return false
		{
			return false;
		}
	}
	else // IF NEXT INDEX OF HEAD IS NULL, return false
	{
		return false;
	}
	
	if( slowptr && fastptr ) // IF BOTH slowptr AND fastptr ARE NOT NULL GO INTO THE WHILE LOOP
	{
		while( slowptr != fastptr ) // ENDS THE WHILE LOOP IF slowptr AND fastptr MEET IN THE SAME INDEX (slowptr == fastptr)
		{
			if( slowptr -> next != NULL ) // IF NEXT INDEX OF slowptr IS NOT NULL
			{	
				slowptr = slowptr -> next; // INCREMENT slowptr TO NEXT
			}
			else
			{
				slowptr = NULL; // IF NEXT INDEX OF slowptr IS NULL, return false (AT THE END OF THE WHILE LOOP)
			}

			if( fastptr -> next != NULL && fastptr -> next -> next != NULL ) // IF NEXT AND NEXT NEXT INDEX OF fastptr IS NOT NULL
			{
				fastptr = fastptr -> next -> next; // INCREMENT fastptr TO NEXT NEXT
			}
			else
			{
				fastptr = NULL; // IF NEXT OR NEXT NEXT INDEX OF fastptr IS NULL, return false (AT THE END OF THE WHILE LOOP)
			}
			
			if( slowptr == NULL || fastptr == NULL ) // IF slowptr OR fastptr IS NULL
			{
				return false; // return false;
			}
		}
		return true; // IT REACHES THIS POINT WHEN slowptr == fastptr (WHEN THEY MEET), IT IS CIRCULAR SO return true;
	}
	else
	{
		return false; // IF slowptr OR fastptr IS NULL, return false
	}
}
