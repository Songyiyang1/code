#include "../lib/HRRN.h"

#include <stdio.h>

static queue_object *HRRN_queue;
//You can add more global variables and structs here
unsigned int time;

float calc_ratio(process* object) {
	return (float)(time-object->start_time)/(object->time_left)+1;
}

process *HRRN_tick(process *running_process)
{
	// TODO
	queue_object* max_pointer=NULL;
	if (running_process == NULL || running_process->time_left <= 0) {
		if (queue_peek(HRRN_queue)==NULL) {
			time++;
			return NULL;
		}
		float max_rr=0;
		queue_object* pointer=HRRN_queue;
		//find the largest ratio (it's always the next element of pointer)
		while (pointer->next != NULL) {
			float rr=calc_ratio(pointer->next->object);
			if (rr>max_rr) {
				max_rr=rr;
				//the one element before max.
				max_pointer=pointer;
			}
			pointer=pointer->next;
		}
		time++;
		if (max_pointer == NULL) return running_process;
		//return and delete the max. ratio
		process* temp=max_pointer->next->object;
		queue_object* to_delete=max_pointer->next;
		max_pointer->next=max_pointer->next->next;
		free(to_delete);
		temp->time_left--;
		return temp;
	}
	running_process->time_left--;
	time++;
	return running_process;
}

int HRRN_startup()
{
	// TODO
	time=0;
	HRRN_queue = new_queue();
	if (HRRN_queue == NULL)
		return 1;
	return 0;
}

process *HRRN_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if (arriving_process==NULL)
		return running_process;
	queue_add(arriving_process,HRRN_queue);
	return running_process;
}

void HRRN_finish()
{
	// TODO
	free_queue(HRRN_queue);
}
