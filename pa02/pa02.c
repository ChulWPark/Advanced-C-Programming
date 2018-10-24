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
  unsigned char spacer[16] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};
  unsigned char name[16] = {0xF, 0xE, 0xD, 0xC, 0xB, 0xA, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int extra2 = 0xFFFFFFFF;
  int f1_bottom = 0xBBBBBBBB; // used as references
	name[56] = 0x7c;
	name[57] = 0x05;
  // TODO: modify name's elements so that the program prints
  // REALLY BAD IF YOU SEE THIS

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
