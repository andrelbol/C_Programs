#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "queue.h"

#define MAX_ITEMS 5
#define NUM_PRODUTORS 3
#define NUM_CONSUMERS 2
#define RAND_ITEM_ATTR 1000 // Parameter to get a 0...999 item
#define RAND_SLEEP_ATTR 4 // Parameter to get a 0...3 sleep time

// Queue Struct
typedef struct int_queue_t
{
  struct int_queue_t *prev ;  // ptr para usar cast com queue_t
  struct int_queue_t *next ;  // ptr para usar cast com queue_t
  int id ;
  // outros campos podem ser acrescidos aqui
} int_queue_t ;

int_queue_t *buffer;

// Semaphores
sem_t *s_buffer, *s_item, *s_vaga;

// Produtor e Consumidor

void produtor(){
  int pause;
  int_queue_t *item;
  while(1){
    pause = rand()%RAND_SLEEP_ATTR;
    sleep(pause);

    // Enter critical session
    sem_wait(&s_vaga);
    sem_wait(&s_buffer);

    // Adding item
    item = (int_queue_t *) malloc (sizeof(int_queue_t));
    item->id = rand()%RAND_ITEM_ATTR;
    item->prev = NULL;
    item->next = NULL;
    queue_append((queue_t **) &buffer, (queue_t *) item);

    // Leave critical session
    sem_post(&s_buffer);
    sem_post(&s_item);

    // Print result
    printf("A Thread X produziu ");
    print_elem(item);
  }
}

void consumidor(){
  int pause;
  int_queue_t *aux;
  while(1){
    // Enter critial session
    sem_wait(&s_item);
    sem_wait(&s_buffer);

    // Remove item
    aux = buffer->prev; // Get the last elem of the queue
    queue_remove((queue_t **) &buffer, (queue_t *) aux);

    // Leave critical session
    sem_post(&s_buffer);
    sem_post(&s_vaga);
    print_elem(aux);
    pause = rand()%RAND_SLEEP_ATTR;
    sleep(pause);
  }
}

void print_elem (void *ptr)
// Given an element, print it on the screen
{
  int_queue_t *elem = ptr ;

  if (!elem)
  return ;

  elem->prev ? printf ("%d", elem->prev->id) : printf ("*") ;
  printf ("<%d>", elem->id) ;
  elem->next ? printf ("%d", elem->next->id) : printf ("*") ;
}

//Main

int main(){
  // Initializing semaphores
  // Buffer semaphore is binary
  sem_init(&s_buffer, 0, 1);

  // Vacancy semaphore can have MAX_ITEMS items
  sem_init(&s_vaga, 0, MAX_ITEMS);

  // Item semaphore starts nulled
  sem_init(&s_item, 0, 0);
  return 0;
}
