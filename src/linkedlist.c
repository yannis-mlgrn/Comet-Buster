#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

/* Initialisation of the list
 * */

list_ptr list_new(void)
{
  return NULL;
}

/* Add a new cel to a list. 
 *  store the sprite_t to the new cel
 * */
list_ptr list_add(sprite_t sprite, list_ptr list)
{
  list_ptr new_node = (list_ptr)malloc(sizeof(s_list_node_t)); // Allow memory to the new node
  new_node -> data = sprite;
  new_node -> next = list; // Add the new node to the top of the list
  return new_node;
}

/* Return the length of a list
 * */
int list_length(list_ptr l)
{
  list_ptr elt = l;
  int i = 0;
  while (elt != NULL) {
    i++;
    elt = elt->next;
  }
  return i;
}

/* Reverse the order of a list
 * */
void list_reverse(list_ptr * l)
{
  list_ptr previous = NULL;
  list_ptr current = *l;
  list_ptr next_node = NULL;

  while (current != NULL) {
    next_node = current->next;
    
    current->next = previous;
    previous = current;
    current = next_node;
  }
  *l = previous;
}

/* Copy a list to another one. 
 *  Return the new list
 * */
list_ptr list_clone(list_ptr list)
{
  list_ptr new_list = NULL;
  list_ptr current = list;
  list_ptr last_new_node = NULL;
  while (current != NULL) {
    list_ptr new_node = (list_ptr)malloc(sizeof(s_list_node_t));
    if (new_node == NULL) {
      return NULL;
    }
    
    new_node->data = current->data; 
    new_node->next = NULL;

    if (new_list == NULL) {
      new_list = new_node;
      last_new_node = new_node;
    } else {
      last_new_node->next = new_node;
      last_new_node = new_node;
    }

    current = current->next;
  }
  
  return new_list;
}
/* Return true if the list is empty
 * */
bool list_is_empty(list_ptr l)
{
  return l == NULL;
}

/* Search the first cel of the list & 
 *  return the associated sprite 
 * */
sprite_t list_head_sprite(list_ptr l)
{
  if (!list_is_empty(l)) {
    return l->data;
  } else {
    sprite_t default_sprite = {0};
    return default_sprite;
  }
}

/* Return the next cel in list or NULL
 * */
list_ptr list_next(list_ptr l)
{
  if (!list_is_empty(l)) {
    return l->next;
  } else {
    return NULL;
  }
}

/* Search the last cel of a list 
 *  Remove the cel from the list
 *  Return the associated sprite
 * */
sprite_t list_pop_sprite(list_ptr * l)
{
  sprite_t default_sprite = {0}; 
  
  if (*l == NULL) {
    return default_sprite;
  }

  list_ptr current = *l;
  list_ptr previous = NULL;

  if (current->next == NULL) {
    sprite_t data = current->data;
    
    free(current);
    
    *l = NULL;
    
    return data;
  }

  while (current->next != NULL) {
    previous = current;
    current = current->next;
  }

  sprite_t data = current->data;

  previous->next = NULL;

  free(current);

  return data;
}

/* Remove the given cel in a list
 * The list is modified in place.
 * */
void list_remove(list_ptr elt, list_ptr *l)
{
  if (*l == NULL || elt == NULL) {
    return;
  }

  if (*l == elt) {
    *l = elt->next;
    free(elt);
    return;
  }

  list_ptr current = *l;
  while (current->next != NULL && current->next != elt) {
    current = current->next;
  }

  if (current->next == elt) {
    current->next = elt->next;
    free(elt);
  }
}

/* Wipe out a list. 
 *  Don't forget to sprite_free() for each sprite
 * */
void list_free(list_ptr l)
{
  list_ptr current = l;
  list_ptr next_node;

  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }
}
