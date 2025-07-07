#include"../lib/scheduler.h"
#include"../lib/process.h"
#include "helpers.h"
#include<stdlib.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        MLF

int main() {
  /*Defining the processes                Arrival Dur.    Prio    ID
                                          uint    uint    (idc)   char*/
  process processes[PROCESS_COUNT] = {{   0,      7,      0,      'A'},
                                      {   2,      4,      0,      'B'},
                                      {   3,      3,      0,      'C'},
                                      {   6,      2,      0,      'D'},
                                      {   8,      4,      0,      'E'}};
  char* expected_result = "AAABCBBDECCDEEAAAABE";
  print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

  char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

  unsigned int err = compare_result(resulting_schedule, expected_result);
  free(resulting_schedule);
  exit(err);
}