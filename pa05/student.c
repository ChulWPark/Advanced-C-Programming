// Do not remove #ifdef ... #endif before and after each function.
// 
// They are used to test different functions in your program and give
// partial credits, in case your program does not work completely.

#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StudentPrint(Student * stu, int num)
{
  printf("There are %d students\n", num);
  for (int ind = 0; ind < num; ind ++)
    {
      printf("ID = %d, First Name = %s, Last Name = %s\n",
	     stu[ind].ID,  stu[ind].firstname, stu[ind].lastname);
    }
}

#ifdef TEST_READ
// return false if anything is wrong 
// return true if reading the file successfully and the data is save in
// the allocated memory
// input: filename, the name of the input file
// output: address of the allocated memory
// output: number of students
bool StudentRead(char * filename, Student * * stu, int * numelem)
{
  // open the file to read

	FILE *db1 = fopen(filename, "r");

  // if fopen fails, return false
  // do not use fclose since fopen already fails

	if(db1 == NULL)
	{
		return false;
	}

  // count the number of lines to determine the number of students
  // variable line declaration
	*numelem = 0;
	int line = 0;

	while( !feof(db1) )
	{
		line = fgetc(db1);
		if(line == '\n')
		{
			(*numelem)++;
		}
	}

  // return to the beginning of the file
  // you can use fseek or
  // fclose followed by fopen
  // You need to check whether fseek or fopen fails
  // Do not use rewind because it does not report whether it fails

	if( fseek( db1, 0, SEEK_SET ) != 0)
	{
		return false;
	}

  // allocate memory for the data
	Student * data = malloc(sizeof(Student) * (*numelem));
	* stu = data;
  // check whether memory allocation fails
	
	if(data == NULL)
	{
		return false;
	}

  // read the data from the file and store the data in the allocated memory
	for (int i = 0; i < *numelem; i++)
	{
		fscanf(db1, "%d %s %s\n", &(((*stu)[i]).ID), (*stu)[i].firstname, (*stu)[i].lastname);
	}

  // close the file

	fclose(db1);

  return true;
}
#endif

#ifdef TEST_WRITE
// return false if anything is wrong 
// return true if writing the file successfully
// input: filename, the name of the output file
// input: address of the student array
// input: number of students

bool StudentWrite(char * filename, Student * stu, int numelem)
{
  // open the file to write 

	FILE * db2 = fopen(filename, "w");

  // if fopen fails, return false
  // do not use fclose since fopen already fails

	if(db2 == NULL)
	{
		return false;
	}

  // write the students to the output file
	for (int i = 0; i < numelem; i++) 
	{
		if(fprintf(db2, "%d %s %s\n", stu[i].ID, stu[i].firstname, stu[i].lastname) < 1)
		{
			return false;
		}
	}

	fclose(db2);

	return true;

}
#endif 


#ifdef TEST_SORTID
int CompFuncID (const void * a, const void * b)
{
	const Student * ptr1 = (const Student *) a;
	const Student * ptr2 = (const Student *) b;
	const int ida = ptr1->ID;
	const int idb = ptr2->ID;
	return(ida - idb);
}

void StudentSortbyID(Student * stu, int numelem)
{
	qsort(stu, numelem, sizeof(Student), CompFuncID);
}
#endif

#ifdef TEST_SORTFIRSTNAME
int CompFuncfirstname (const void * a, const void * b)
{
	const Student * ptr1 = (const Student *) a;
	const Student * ptr2 = (const Student *) b;
	const char * fna = ptr1->firstname;
	const char * fnb = ptr2->firstname;
	return strcmp(fna, fnb);
}

void StudentSortbyFirstName(Student * stu, int numelem)
{
	qsort(stu, numelem, sizeof(Student), CompFuncfirstname);
}
#endif

#ifdef TEST_SORTLASTNAME
int CompFunclastname (const void * a, const void * b)
{
	const Student * ptr1 = (const Student *) a;
	const Student * ptr2 = (const Student *) b;
	const char * lna = ptr1->lastname;
	const char * lnb = ptr2->lastname;
	return strcmp(lna, lnb);

}

void StudentSortbyLastName(Student * stu, int numelem)
{
	qsort(stu, numelem, sizeof(Student), CompFunclastname);
}
#endif
