#include "linkedlist.h"

node_t * insert(node_t ** head, int index, int value)
{
  if (head == NULL)
  {
    return NULL;
  }

  // allocate memory for node we wish to insert
  node_t * obj_add = malloc(sizeof(*obj_add));
  if (obj_add == NULL)
  {
    return NULL;
  }
  obj_add->data = value;
  obj_add->next = NULL;

  // if the head node doesn't exist our new node
  // is the head. this is why we wanted a reference
  // to the head, so we can modify it if we need to.
  if (*head == NULL)
  {
    *head = obj_add;
    return obj_add;
  }

  // special case of having to insert myself at the beginning
  // so the head will need to be modified
  if (index == 0)
  {
    node_t * old_head = *head;
    *head = obj_add;
    (*head)->next = old_head;
    return obj_add;
  }

  // otherwise we need to iterate through the list to find
  // where I need to insert this node at the index specified
  node_t *prev = *head;
  node_t *cur = (*head)->next;
  int i;
  for (i = 1; (i < index) && (cur != NULL); i++) 
  {
    prev = prev->next;
    cur = cur->next;
  }

  // if we didn't reach the index that means the list
  // isn't long enough and we don't want to add at an
  // index that can't exist
  if (i != index)
  {
    free(obj_add);
    return NULL;
  }

  prev->next = obj_add;
  obj_add->next = cur;
  return obj_add;
}

bool rem(node_t ** head, int index)
{
  if (head == NULL || *head == NULL)
  {
     return false;
  }

  if (index == 0)
  {
    // this is actually a special case where the head
    // pointer will need to be changed so the next element
    // is the new first element.
    // it's also why we pass a reference to head, so this
    // method can change it if needed
    node_t * old_head = *head;
    *head = (*head)->next;
    free(old_head);
    return true;
  }

  // keep track of the previous node so I can link it
  // to where the next node of the node I'm removing
  node_t *prev = *head;
  node_t *cur = (*head)->next;

  // advnace until I reached the index I'm removing
  // or until I've reached the end of the linked list
  int i;
  for (i = 1; (i < index) && (cur != NULL); i++) 
  {
    prev = prev->next;
    cur = cur->next;
  }

  // if we didn't reach the index that means the list
  // isn't long enough and we don't want to go out of bounds
  if (i == index)
  {
    // link previous to current
    prev->next = cur->next;
    free(cur);
    return true;
  }

  return false;
}

node_t * get(const node_t * head, int index)
{
  for (int i = 0; (i < index) && (head != NULL); i++)
  {
    head = head->next;
  }
  return (node_t *)head;
}

int length(const node_t * head)
{
  int count;
  for (count = 0; head != NULL; count++)
  {
    head = head->next;
  }

  return count;
}

void printlist(const node_t * head)
{
  printf("head: %p\n", (void *)head);
  while (head != NULL)
  {
    printf("%p: data = %d, next = %p\n", (void *)head, head->data, (void *)(head->next));
    head = head->next;
  }
}
