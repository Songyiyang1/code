#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   4
#define RR_QUANTUM      2
#define STRATEGY        LCFSPR

int main()
{
  /*Defining the processes                Arrival Dur.    Prio    ID
                                          uint    uint    uint    char*/
  process processes[PROCESS_COUNT] = {{   0,      1,      1,      'S'},
                                      {   3,      3,      1,      'A'},
                                      {   4,      2,      4,      'B'},
                                      {   5,      2,      2,      'C'}};
  char* expected_result = "S  ABCCAAB";
  print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

  char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

  unsigned int err = compare_result(resulting_schedule, expected_result);
  free(resulting_schedule);
  exit(err);
}