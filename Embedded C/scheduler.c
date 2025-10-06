#include <stdio.h>

typedef struct TaskType {
 
    u_int32_t period;   // rate at which task should tick
    u_int32_t elapsedTime; // time since last tick
    // Pointer to function goes HERE!!!!

} TaskType ;

TaskType Tasks[2];              // array to hold tasks 
