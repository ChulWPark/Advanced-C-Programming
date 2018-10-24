// You must modify this file
#ifndef PA05_H
#define PA05_H
#include "constant.h"
#include <stdbool.h>

// create a structure type that has the following attributes
// please make sure the names are exactly the same
//  int- ID
//  char- firstname[NAME_LENGTH]
//  char- lastname[NAME_LENGTH]
typedef struct
{
	int ID;
	char firstname[NAME_LENGTH];
	char lastname[NAME_LENGTH];
} Student;

// functions to be implemented
bool StudentRead(char * filename, Student * * stu, int * numelem);
bool StudentWrite(char * filename, Student * stu, int numelem);
void StudentSortbyID(Student * stu, int numelem);
void StudentSortbyFirstName(Student * stu, int numelem);
void StudentSortbyLastName(Student * stu, int numelem);

// function already impelemented for you
void StudentPrint(Student * stu, int num);
#endif
