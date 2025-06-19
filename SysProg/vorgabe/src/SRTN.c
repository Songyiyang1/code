#include "../lib/SRTN.h"

#include <stdio.h>

static queue_object *SRTN_queue;
//You can add more global variables here

process *SRTN_tick(process *running_process)
{
	// TODO
	if (running_process == NULL || running_process->time_left <= 0) {
		if (queue_peek(SRTN_queue)==NULL) {
			return NULL;
		}
		process *temp = queue_poll(SRTN_queue);
		temp->time_left --;
		return temp;
	}
	running_process->time_left --;
	return running_process;
}

int SRTN_startup()
{
	// TODO
	SRTN_queue = new_queue();
	if (SRTN_queue == NULL)
		return 1;
	return 0;
}

process *SRTN_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if (arriving_process == NULL) {
		return running_process;
	}
	if (SRTN_queue->next == NULL) {
		if (running_process!=NULL && running_process->time_left >arriving_process->time_left ) {
			queue_object *pointer = SRTN_queue;
			while (pointer->next != NULL && ((process *)pointer->next->object)->time_left >
							    running_process->time_left) {
				pointer = pointer->next;
							    }
			queue_object *new_process = (queue_object *)malloc(sizeof(queue_object));
			new_process->object = running_process;
			new_process->next = pointer->next;
			pointer->next = new_process;
			return arriving_process;
		}
		queue_add(arriving_process, SRTN_queue);
		return running_process;
	}
	//if process with less remaining time comes, then process this first
	if (arriving_process->time_left<running_process->time_left) {
		queue_object *pointer = SRTN_queue;
		while (pointer->next != NULL && ((process *)pointer->next->object)->time_left >
						    running_process->time_left) {
			pointer = pointer->next;
						    }
		queue_object *new_process = (queue_object *)malloc(sizeof(queue_object));
		new_process->object = running_process;
		new_process->next = pointer->next;
		pointer->next = new_process;
		return arriving_process;
	}
	//else sort by remaining time
	queue_object *pointer = SRTN_queue;
	while (pointer->next != NULL && ((process *)pointer->next->object)->time_left >
					    arriving_process->time_left) {
		pointer = pointer->next;
					    }
	queue_object *new_process = (queue_object *)malloc(sizeof(queue_object));
	new_process->object = arriving_process;
	new_process->next = pointer->next;
	pointer->next = new_process;
	return running_process;
}

void SRTN_finish()
{
	// TODO
	free_queue(SRTN_queue);
}
