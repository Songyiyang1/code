#include "../lib/LCFSPR.h"

static queue_object* LCFSPR_queue;
//You can add more global variables here
static queue_object* waiting_queue;

process* LCFSPR_tick (process* running_process){
    // TODO
    if (running_process == NULL || running_process->time_left <= 0) {
        if (queue_peek(waiting_queue)==NULL) {
            return NULL;
        }
        process *temp = queue_poll(waiting_queue);
        temp->time_left --;
        return temp;
    }
    running_process->time_left --;
    return running_process;
}

int LCFSPR_startup(){
    // TODO
    LCFSPR_queue = new_queue();
    waiting_queue = new_queue();
    if (LCFSPR_queue == NULL || waiting_queue == NULL)
        return 1;
    return 0;
}

process* LCFSPR_new_arrival(process* arriving_process, process* running_process){
    // TODO
    if (arriving_process==NULL) {
        return running_process;
    }
    if (running_process==NULL) {
        return arriving_process;
    }
    if (running_process->time_left >0) {
        queue_add(running_process, waiting_queue);
    }
    return arriving_process;
}

void LCFSPR_finish(){
	// TODO
    free_queue(waiting_queue);
    free_queue(LCFSPR_queue);
}
