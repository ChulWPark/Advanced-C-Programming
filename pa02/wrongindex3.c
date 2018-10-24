#include <stdio.h>
#include <stdlib.h>

void dummy()
{
  int x;
  return;
}

void f1(void) 
{
  int f1_top = 0xAAAAAAAA; // used as references
  char name[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int f1_bottom = 0xBBBBBBBB; // used as references
  name[40] = 0x1d; //These values may have to change
  name[41] = 0x05; //These values may have to change
  dummy();
}

void f2(void) 
{
  int f2_top = 0xCCCCCCCC; // used as references
  char message[] = "REALLY BAD IF YOU SEE THIS\n"; 
  printf(message);
  int f2_btm = 0xDDDDDDDD; // used as references
}

int main(int argc, char * * argv) 
{
  int main_top = 0xEEEEEEEE; // used as references
  f1();	
  int main_btm = 0xFFFFFFFF; // used as references
  return EXIT_SUCCESS;
}
