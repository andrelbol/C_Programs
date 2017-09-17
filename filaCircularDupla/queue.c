#include <stdio.h>
#include "queue.h"

// Utility functions

int empty_queue(queue_t **queue){
  /*
  Return 1 if queue is empty. Otherwise return 0.
  */
  queue_t *first = *queue;
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
  if(elem->prev != NULL && elem->next != NULL){
    printf("Element is already in another queue.");
    return ;
  }
  // Starting the process of appending
  queue_t *aux;
  // Testing if the queue is empty
  if(empty_queue(queue)){
    aux = elem;
    aux->next = aux;
    aux->prev = aux;
    *queue = aux;
    return;
  }
  aux = (*queue)->prev; // End of the queue
  // Insert the new element
  aux->next = elem;
  elem->prev = aux;
  elem->next = *queue;
  (*queue)->prev = elem;
}

queue_t *queue_remove (queue_t **queue, queue_t *elem){
  // Testing if queue exists
  if(!queue_exists(queue)){
    printf("Queue doesn't exists.");
    return NULL;
  }
  // Testing if element exists
  if(!element_exists(elem)){
    printf("Element doesn't exists.");
    return NULL;
  }
  // Testing if the queue is empty
  if(empty_queue(queue)){
    printf("Queue is empty");
    return NULL;
  }
  queue_t *aux = *queue;
  // If it's the first element
  if(elem == *queue){
    if(queue_size(*queue) == 1){ // Unique element
      *queue = NULL;
    }
    else{
      elem->prev->next = elem->next;
      elem->next->prev = elem->prev;
      *queue = elem->next;
    }
    elem->next = NULL;
    elem->prev = NULL;
    return elem;
  }
  while(aux->next != *queue){
    aux = aux->next;
    if(aux == elem){ // Encontrando o elemento, retira e retorna
      aux->prev->next = aux->next;
      aux->next->prev = aux->prev;
      aux->next = NULL;
      aux->prev = NULL;
      return aux;
    }
  }
  // não encontrou o elemento, assim ele não existe na fila
  printf("The element isn't in this queue");
  return NULL;
}

int queue_size (queue_t *queue){
  int num_elem = 1;
  queue_t *aux = queue;
  //Testing if queue is empty
  if(queue == NULL){
    return 0;
  }
  // Counting elements
  while(aux->next != queue){
    aux = aux->next;
    num_elem++;
  }
  return num_elem;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ){
  printf("%s: [", name);
  if(queue == NULL){
    return;
  }
  queue_t *aux = queue;
  print_elem((void*) aux);
  while(aux->next != queue){
    aux = aux->next;
    printf(" ");
    print_elem((void*) aux);
  }
  printf("]\n");
}
