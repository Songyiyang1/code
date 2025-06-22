#include "../lib/scheduler.h"
#include "../lib/process.h"
#include "helpers.h"
#include <stdlib.h>

#define RR_QUANTUM      10
#define STRATEGY        RR

int main() {
    /*Defining the processes   Arrival Dur.    Prio    ID
                               uint    uint    (idc)   char*/
    process processes[] = {{   0,      5,      0,      'A'},
                           {   2,      3,      0,      'B'},
                           {   5,      7,      0,      'C'}};
    const int PROCESS_COUNT = sizeof(processes)/sizeof(process);

    char* expected_result = "AAAAABBBCCCCCCC";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    
    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
