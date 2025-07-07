#include "../lib/scheduler.h"
#include "../lib/process.h"
#include "helpers.h"
#include <stdlib.h>

#define RR_QUANTUM      1
#define STRATEGY        RR

int main() {
    /*Defining the processes   Arrival Dur.    Prio    ID
                               uint    uint    (idc)   char*/
    process processes[] = {{   0,      3,      0,      'A'},
                           {   2,      2,      0,      'B'},
                           {   3,      1,      0,      'C'},
                           {   5,      3,      0,      'D'},
                           {   8,      2,      0,      'E'},
                           {   9,      3,      0,      'F'},
                           {  12,      1,      0,      'G'}};
    const int PROCESS_COUNT = sizeof(processes)/sizeof(process);

    char* expected_result = "AABACBDDEDFEFGF";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    
    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
