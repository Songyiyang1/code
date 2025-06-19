#include "../lib/MLF.h"

static queue_object **MLF_queues;
//You can add more global variables here
static int level;
static unsigned int run_time;
static unsigned int* quantum;

process *MLF_tick(process *running_process)
{
	// TODO
	//if process is done, kick it out from queue
	if (running_process!=NULL && running_process->time_left<=0) {
		if (level<3) {
			queue_poll(MLF_queues[level]);
		}
		else {
			queue_poll_tail(MLF_queues[level]);
		}
		running_process=NULL;
		run_time=0;
	}
	//if process reaches time limit, put it in next level
	if (level<3 && run_time>=quantum[level]) {
		queue_add(queue_poll(MLF_queues[level]),MLF_queues[level+1]);
		level++;
		running_process=NULL;
		run_time=0;
	}
	//check for process with higher priority
	for (int i=0;i<3;i++) {
		if (queue_peek(MLF_queues[i]) == NULL) {
			continue; //no process in this level
		}
		if (i<level) {
			level=i;
			run_time=0;
			break;
		}
	}
	if (level<3) {
		running_process=queue_peek(MLF_queues[level]);
		if (running_process==NULL)
			return NULL;
		run_time++;
		running_process->time_left--;
	}
	else {
		running_process=MLF_queues[3]->next->object;
		if (running_process==NULL)
			return NULL;
		run_time++;
		running_process->time_left--;
	}
	return running_process;
}

int MLF_startup()
{
	// TODO
	MLF_queues = malloc(4 * sizeof(queue_object *));
	quantum = malloc(3 * sizeof(unsigned int));
	quantum[0] = 1;
	quantum[1] = 2;
	quantum[2] = 6;
	if (MLF_queues == NULL)
		return 1;
	for (int i = 0; i < 4; i++) {
		MLF_queues[i] = new_queue();
		if (MLF_queues[i] == NULL)
			return 1;
	}
	level=4;
	return 0;
}


process *MLF_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if (arriving_process == NULL)
		return running_process;
	queue_add(arriving_process, MLF_queues[0]);
	return running_process;
}

void MLF_finish()
{
	// TODO
	for (int i = 0; i < 4; i++) {
		free_queue(MLF_queues[i]);
	}
	free(quantum);
	free(MLF_queues);
}
