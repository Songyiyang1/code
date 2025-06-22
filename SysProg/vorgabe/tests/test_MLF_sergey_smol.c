#include "../lib/scheduler.h"
#include "../lib/process.h"
#include "helpers.h"
#include <stdlib.h>

#define RR_QUANTUM      2
#define STRATEGY        MLF

int main() {
    /*Defining the processes   Arrival Dur.    Prio    ID
                               uint    uint    (idc)   char*/
    process processes[] = {{   0,      1,      0,      'A'},
                           {   2,      1,      0,      'B'},
                           {   3,      1,      0,      'C'},
                           {   6,      1,      0,      'D'},
                           {   8,      1,      0,      'E'}};
    const int PROCESS_COUNT = sizeof(processes)/sizeof(process);

    char* expected_result = "A BC  D E";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    
    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
