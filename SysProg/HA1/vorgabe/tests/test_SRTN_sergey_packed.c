#include "../lib/scheduler.h"
#include "../lib/process.h"
#include "helpers.h"
#include <stdlib.h>

#define RR_QUANTUM      2
#define STRATEGY        SRTN

int main() {
    /*Defining the processes   Arrival Dur.    Prio    ID
                               uint    uint    (idc)   char*/
    process processes[] = {{   0,      2,      0,      'A'},
                           {   1,      5,      0,      'B'},
                           {   2,      7,      0,      'C'},
                           {   3,      3,      0,      'D'},
                           {   4,      1,      0,      'E'},
                           {   5,      4,      0,      'F'},
                           {   6,      7,      0,      'G'}};
    const int PROCESS_COUNT = sizeof(processes)/sizeof(process);

    char* expected_result = "AABDEDDBBBBFFFFCCCCCCCGGGGGGG";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    
    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
