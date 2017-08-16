#include "queue.h"

// Utility functions

int empty_queue(queue_t **queue){
  /*
    Return 1 if queue is empty. Otherwise return 0.
  */
  queue_t first = *queue;
  if(first == NULL){
    return 1;
  }
  return 0;
}

int queue_exists(queue_t **queue){
  /*
    Return 1 if queue exists. Otherwise return 0.
  */
  if(queue == NULL){
    return 0;
  }
  return 1;
}

int element_exists(queue_t *elem){
  /*
    Return 1 if element exists. Otherwise return 0.
  */
  if(elem == NULL){
    return 0;
  }
  return 1;
}

// Main functions for the queue

void queue_append(queue_t **queue, queue_t *elem){
  // Testing if queue exists
  if(!queue_exists(queue)){
    printf("Queue doesn't exists.");
    return ;
  }
  // Testing if element exists
  if(!element_exists(elem)){
    printf("Element doesn't exists.");
    return ;
  }
  // Testing if element is in another queue
  if(!elem->prev || !elem->next){
    printf("Element is already in another queue.")
    return ;
  }
  // Starting the process of appending
  queue_t *first = *queue;
  queue_t *aux = first;
  // Testing if the queue is empty
  if(empty_queue(queue)){
    first = elem;
    first->next = first;
    first->prev = first;
    return;
  }
  // Walk to the end of the queue
  while(aux->next != first){
    aux = aux->next;
  }
  // Insert the new element
  aux->next = elem;
  elem->prev = aux;
  elem->next = first;
  first->prev = elem;
  return;
}

queue_t *queue_remove (queue_t **queue, queue_t *elem){
  // TODO
  return NULL;
}

int queue_size (queue_t *queue){
  return 0;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ){
  // TODO
}
