// You must modify this file
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "student.h"
#include "msort.h"
// --------------------------------------------------------------
int main(int argc, char * * argv)
{
  // argv[1]: input file name
  // argv[2]: output file name, sorted by ID
  // argv[3]: output file name, sorted by first name
  // argv[4]: output file name, sorted by last name
  if (argc < 5)
    {
      return EXIT_FAILURE;
    }
  Student * stu;
  int numelem;
  if (StudentRead(argv[1], & stu, & numelem) == false)
  {
      return EXIT_FAILURE;
  }

  StudentPrint(stu, numelem);
  StudentSortbyID(stu, numelem);
  StudentPrint(stu, numelem);
  if (StudentWrite(argv[2], stu, numelem) == false)
    {
      return EXIT_FAILURE;
      }
  StudentSortbyFirstName(stu, numelem);
  StudentPrint(stu, numelem);
  if (StudentWrite(argv[3], stu, numelem) == false)
    {
      return EXIT_FAILURE;
      }
  StudentSortbyLastName(stu, numelem);
  StudentPrint(stu, numelem);
  if (StudentWrite(argv[4], stu, numelem) == false)
    {
      return EXIT_FAILURE;
      }
  free (stu);
  return EXIT_SUCCESS;
}
