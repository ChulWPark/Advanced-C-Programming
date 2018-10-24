#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
  int data;
  struct node * next;
} node_t;

node_t * insert(node_t ** head, int index, int value);
bool rem(node_t ** head, int index);

node_t * get(const node_t * head, int index);
int length(const node_t * head);

void printlist(const node_t * head);
#endif
