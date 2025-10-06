
#include "scheduler.h"


#define SYST_CSR (*(volatile uint32_t*) 0xE000E010)	//sys-tick control and status register
#define SYST_RVR (*(volatile uint32_t*) 0xE000E014)	// reload value register
#define SYST_CVR (*(volatile uint32_t*) 0xE000E018)		// current val register, write any value to clear

static volatile uint32_t systick_ms = 0;		// holds elapsed ms

void initSysTick(uint32_t time_base){

	SYST_RVR = time_base - 1; // load tick time into RVR
	SYST_CVR = 0;			// write value to CVR to clear it
	SYST_CSR = (1U << 0) | (1U << 1) | (1U << 2);	// enable, tick-int and clk-source set

}

void SysTick_Handler(void){

	systick_ms++;		// each time interrupt triggered by systick (every ms) increment counter

}

void scheduler(void){


	static uint32_t last_time = 0;
	uint32_t now = systick_ms;
	uint32_t time_difference = now - last_time;
	last_time = now;

	uint8_t i = 0;
	for (i=0; i<TOTAL_TASKS; i++){	// for each task

		if(TaskList[i].elapsedTime >= TaskList[i].period){	// if elapsed time > period

			TaskList[i].TaskPtr();		// call the tasks function
			TaskList[i].elapsedTime = 0;	// reset elapsed time
		}
		TaskList[i].elapsedTime += time_difference;
	}
}
