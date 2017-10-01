#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"

// Defining task states
#define NEW 0
#define READY 1
#define EXEC 2
#define ENDED 3

// Defining processor states
#define FREE 0
#define BUSY 1

// Max of tasks
#define MAX_TASKS 20

// Max time
#define TMAX 8

typedef struct task_queue_t {
  struct task_queue_t *prev;
  struct task_queue_t *next;
  int id; // Identificator
  int begin, end; // Begin time and End time of the Task
  int all_duration, current_duration; // Needed duration and how long it is in processor
  int static_priority, dynamic_priority;
  int state; // Current state
} task_queue_t;

// Global Variables
task_queue_t * all_tasks;
task_queue_t * ready_tasks;
task_queue_t * ended_tasks;
task_queue_t * current_task = NULL;

// Processor state
int cpu_state = FREE;

// Other ones
int t = 0;
int task_quantity;




task_queue_t *create_task(int id, int created_at, int exec_time, int priority){
  task_queue_t *new_task = (task_queue_t *) malloc(sizeof(task_queue_t));
  new_task->prev = NULL;
  new_task->next = NULL;
  new_task->id = id;
  new_task->begin = created_at;
  new_task->all_duration = exec_time;
  new_task->static_priority = priority;
  new_task->dynamic_priority = 0;
  new_task->end = created_at + exec_time;
  new_task->current_duration = 0;
  new_task->state = NEW;

  return new_task;
}

void get_input(){
  // Get a file passed in argv and convert into tasks
  int i=0;
  int created_at, exec_time, priority;
  task_queue_t *new_task;
  while(i<task_quantity){
    scanf("%d %d %d", &created_at, &exec_time, &priority);
    new_task = create_task(i, created_at, exec_time, priority);
    queue_append((queue_t **) &all_tasks, (queue_t *) new_task);
    i++;
  }
}

void print_header(){
  int i=0;

  printf("Tempo:\t");
  for(i=0; i<task_quantity; i++){
    printf("P%d\t", i);
  }
  printf("\n");;
}

void print_current_state(){
  int i;
  task_queue_t *iterator;

  printf("%d- %d\t", t, (t+1));
  iterator = all_tasks;
  do {
    if(iterator->state == EXEC){
      printf("##");
    }
    else{
      printf("--");
    }
    printf("\t");
  } while(iterator != all_tasks);

}

int main(int argc, char const *argv[]){
  int task_finish_time;  // Mark the finish time of the current task
  task_queue_t *iterator; // User for iterating in queue
  int i=0;


  printf("Digite quantos processos você deseja: \n");
  scanf("%d", &task_quantity);  // Fill the global variable with the quantity

  get_input(); // Fill the queue with tasks
  print_header();

  // TODO: printar o cabeçalho
  while(t < TMAX){

    // Verifying if the task in cpu has already terminated
    if(cpu_state == BUSY){ // If there is a task in cpu
      if(current_task->current_duration == current_task->all_duration){
        current_task->state = ENDED; // Finish the task
        queue_append((queue_t **) ended_tasks, (queue_t *) current_task);
        current_task = NULL; // No current task
        cpu_state = FREE;
      }
      /* Here would enter the quantum verification in Round Robin method*/
    }

    // Verifying if there is a task to start now
    iterator = all_tasks;
    do {  // For each task
      if(iterator->begin == t){
        // queue_remove((queue_t **) all_tasks, (queue_t *) iterator);
        // queue_append((queue_t **) ready_tasks, (queue_t *) iterator);
        iterator->state = READY;
      }
      iterator = iterator->next;
    } while(iterator != ready_tasks);

    // Adding a new task to cpu if it's free
    if(cpu_state == FREE){
      if(ready_tasks != NULL){
        // current_task = (task_queue_t *) queue_remove((queue_t **) ready_tasks, (queue_t *) ready_tasks);
        current_task = ready_tasks;
        current_task->state = EXEC;
        printf("DEBUG\n");
      }
    }

    print_current_state();
    t++;
  }

  // TODO: calcular e imprimir tempos médios
  return 0;
}
