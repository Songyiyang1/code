#include "../lib/scheduler.h"
#include "../lib/process.h"
#include "helpers.h"
#include <stdlib.h>

#define RR_QUANTUM      2
#define STRATEGY        MLF

int main() {
    /*Defining the processes   Arrival Dur.    Prio    ID
                               uint    uint    (idc)   char*/
    process processes[] = {{   0,      20,      0,      'A'},
                           {   1,      16,      0,      'B'},
                           {   5,      14,      0,      'C'},
                           {   7,      12,      0,      'D'},
                           {  10,      10,      0,      'E'}};
    const int PROCESS_COUNT = sizeof(processes)/sizeof(process);

    char* expected_result =
        "ABAABBCDCCEDDEEAAAAAABBBBBBCCCCCCDDDDDDEEEEEEEDDDCCCCCBBBBBBBAAAAAAAAAAA";
    print_schedule_info(PROCESS_COUNT, STRATEGY, 0, processes);

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);
    
    unsigned int err = compare_result(resulting_schedule, expected_result);
    free(resulting_schedule);
    exit(err);
}
