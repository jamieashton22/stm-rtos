#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "stm32f401xe.h"
#include "core_cm4.h"

#define TOTAL_TASKS 3

typedef struct TaskType{				// Task Control Block structure (TCB)

	uint32_t period;		// time between runs
	uint32_t elapsedTime;	// time since last run
	void (*TaskPtr)(void);	// function ptr points to task function
} TaskType ;

extern TaskType TaskList[TOTAL_TASKS];

extern void scheduler(void);

extern void SysTick_Handler(void);
extern void initSysTick(uint32_t time_base);


#endif
