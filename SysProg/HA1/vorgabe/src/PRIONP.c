#include "../lib/PRIONP.h"

#include <stdio.h>

static queue_object *PRIONP_queue;
// You can add more global variables here

process *PRIONP_tick(process *running_process) {
  // TODO
  if (running_process == NULL || running_process->time_left <= 0) {
    if (queue_peek(PRIONP_queue)==NULL) {
      return NULL;
    }
    process *temp = queue_poll(PRIONP_queue);
    temp->time_left --;
    return temp;
  }
  running_process->time_left --;
  return running_process;
}

int PRIONP_startup() {
  // TODO
  PRIONP_queue = new_queue();
  if (PRIONP_queue == NULL)
    return 1;
  return 0;
}

process *PRIONP_new_arrival(process *arriving_process,
                            process *running_process) {
  // TODO
  if (arriving_process == NULL) {
    return running_process;
  }

  if (PRIONP_queue->next == NULL) {
    queue_add(arriving_process, PRIONP_queue);
    return running_process;
  }

  queue_object *pointer = PRIONP_queue;
  while (pointer->next != NULL && ((process *)pointer->next->object)->priority <
                                      arriving_process->priority) {
    pointer = pointer->next;
  }
  queue_object *new_process = (queue_object *)malloc(sizeof(queue_object));
  new_process->object = arriving_process;
  new_process->next = pointer->next;
  pointer->next = new_process;
  return running_process;
}

void PRIONP_finish() {
  // TODO
  free_queue(PRIONP_queue);
}
