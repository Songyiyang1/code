#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        HRRN

int main()
{
  /*Defining the processes                Arrival Dur.    Prio    ID
                                          uint    uint    uint    char*/
  process processes[PROCESS_COUNT] = {{   0,      1,      1,      'S'},
                                      {   3,      5,      3,      'A'},
                                      {   4,      3,      4,      'B'},
                                      {   5,      2,      2,      'C'},
                                      {   6,      1,      2,      'D'}};
  char* expected_result = "S  AAAAADCCBBB";
  print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

  printf("\nThis test checks for: \n -handling of empty ticks\n -running process doesnt get disrupted\n -process with highes response ratio is executed next\n \n");

  char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

  unsigned int err = compare_result(resulting_schedule, expected_result);
  free(resulting_schedule);
  exit(err);
}