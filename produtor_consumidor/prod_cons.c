#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "queue.h"

#define MAX_ITEMS 5

// Queue
typedef struct filaint_t
{
  struct filaint_t *prev ;  // ptr para usar cast com queue_t
  struct filaint_t *next ;  // ptr para usar cast com queue_t
  int id ;
  // outros campos podem ser acrescidos aqui
} filaint_t ;
filaint_t *buffer;
filaint_t item[MAX_ITEMS];

// Semaphores
sem_t *s_buffer, *s_item, *s_vaga;

// Index of vector of ints
int i = 0;


void print_elem (void *ptr)
{
  filaint_t *elem = ptr ;

  if (!elem)
  return ;

  elem->prev ? printf ("%d", elem->prev->id) : printf ("*") ;
  printf ("<%d>", elem->id) ;
  elem->next ? printf ("%d", elem->next->id) : printf ("*") ;
}


// Produtor e Consumidor

void produtor(){
  int pause;
  while(1){
    pause = rand()%4;
    sleep(pause);
    sem_wait(&s_vaga);
    sem_wait(&s_buffer);
    // Adding item
    item[i].id = rand()%1000;
    item[i].prev = NULL;
    item[i].next = NULL;

    queue_append((queue_t **) &buffer, (queue_t *) item[i]);
    sem_post(&s_buffer);
    sem_post(&s_item);
    print_elem(item[i]);
    i++;
  }
}

void consumidor(){
  int pause;
  i=0;
  filaint_t aux = buffer;
  while(1){
    sem_wait(&s_item);
    sem_wait(&s_buffer);
    queue_remove((queue_t **) &buffer, (queue_t *) aux);
    sem_post(&s_buffer);
    sem_post(&s_vaga);
    print_elem(aux;)
    pause = rand()%4;
    sleep(pause);
  }
}

void print_elem (void *ptr)
{
  filaint_t *elem = ptr ;

  if (!elem)
  return ;

  elem->prev ? printf ("%d", elem->prev->id) : printf ("*") ;
  printf ("<%d>", elem->id) ;
  elem->next ? printf ("%d", elem->next->id) : printf ("*") ;
}

//Main

int main(){
  return 0;
}
