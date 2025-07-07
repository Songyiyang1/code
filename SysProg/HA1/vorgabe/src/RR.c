#include "../lib/RR.h"

static queue_object *RR_queue;
// You can add more global variables
int interval;
int run_time;

process *RR_tick(process *running_process) {
  // TODO
  if (running_process==NULL || running_process->time_left <= 0) {
    if (queue_peek(RR_queue)==NULL) {
      return NULL;
    }
    process *temp = queue_poll(RR_queue);
    temp->time_left --;
    run_time=1;
    return temp;
  }
  if (run_time >= interval) {
    queue_add(running_process, RR_queue);
    process *temp = queue_poll(RR_queue);
    temp->time_left --;
    run_time=1;
    return temp;
  }
  running_process->time_left --;
  run_time++;
  return running_process;
}

int RR_startup(int quantum) {
  // TODO
  interval = quantum;
  RR_queue = new_queue();
  if (RR_queue == NULL)
    return 1;
  return 0;
}

process *RR_new_arrival(process *arriving_process, process *running_process) {
  // TODO
  if (arriving_process == NULL) {
    return running_process;
  }
  queue_add(arriving_process, RR_queue);
  return running_process;
}

void RR_finish() {
  // TODO
  free_queue(RR_queue);
}
