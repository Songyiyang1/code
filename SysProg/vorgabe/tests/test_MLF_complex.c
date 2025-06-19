#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   4
#define RR_QUANTUM      2
#define STRATEGY        MLF

int main()
{
  /*Defining the processes                Arrival Dur.    Prio    ID
                                          uint    uint    uint    char*/
  process processes[PROCESS_COUNT] = {{   0,      1,      1,      'S'},
                                      {   3,      12,      1,      'A'},
                                      {   4,      11,      1,      'B'},
                                      {   5,      10,      1,      'C'}};
  char* expected_result = "S  ABCAABBCCAAAAAABBBBBBCCCCCCCBBAAA";
  print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

  printf("\nThis test checks for: \n -handling of empty ticks\n -running process doesnt get disrupted\n -FIFO implementation and correct quantum of the first thee queues\n -LCFS implementation of last queue\n \n");

  char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

  unsigned int err = compare_result(resulting_schedule, expected_result);
  free(resulting_schedule);
  exit(err);
}