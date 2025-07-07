#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   4
#define RR_QUANTUM      2
#define STRATEGY        SRTN

int main()
{
  /*Defining the processes                Arrival Dur.    Prio    ID
                                          uint    uint    uint    char*/
  process processes[PROCESS_COUNT] = {{   0,      1,      1,      'S'},
                                      {   3,      5,      1,      'A'},
                                      {   4,      3,      4,      'B'},
                                      {   5,      1,      2,      'C'}};
  const char *expected_result = "S  ABCBBAAAA";
  print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

  char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

  printf("\nThis test checks for: \n handling of empty ticks, \n disrupting current process if another has shorter remaining time\n \n");

  int err = compare_result(resulting_schedule, expected_result);
  free(resulting_schedule);
  exit(err);
}