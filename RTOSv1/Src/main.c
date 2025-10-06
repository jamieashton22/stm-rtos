

// NOTES
// 02/10/25 - setting up a timebase with systick (1 ms). by default cpu uses HSI which is 16MHz, can
// use other ones to get higher clock speeds e.g PLL up to 84 MHz, do this later.

#include <stdint.h>
#include "stm32f401xe.h"
#include "core_cm4.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#define SYST_CSR (*(volatile uint32_t*) 0xE000E010)	//sys-tick control and status register
#define SYST_RVR (*(volatile uint32_t*) 0xE000E014)	// reload value register
#define SYST_CVR (*(volatile uint32_t*) 0xE000E018)		// current val register, write any value to clear


void SysTick_Handler(void);
void initGPIO(void);
void initSysTick(uint32_t time_base);
void scheduler(void);

volatile uint32_t systick_ms = 0;		// holds elapsed ms
#define TOTAL_TASKS 3

typedef struct TaskType{				// Task Control Block structure (TCB)

	uint32_t period;		// time between runs
	uint32_t elapsedTime;	// time since last run
	void (*TaskPtr)(void);	// function ptr points to task function
} TaskType ;

TaskType TaskList[TOTAL_TASKS];		// array to hold tasks, priority determined by order


void initGPIO(void){

	RCC->AHB1ENR |= (1U << 0);				// LED
	GPIOA->MODER &= ~(3U << 10);
	GPIOA->MODER |=(1U << 10);
}

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

void Task1(void){

	// do something

}


void Task2(void){

	// do something

}

void Task3(void){

	// do something

}

// MAIN LOOP --------------------------------------------------------------------------------------------

int main(void)
{

	// TASK ASSIGNMENT

	uint8_t i = 0;

	// TASK 1 - PERIOD & FUNCTION
	TaskList[i].period = 1000;		// task 1 has a period of 1000 ms
	TaskList[i].TaskPtr = &Task1;	// task 1s pointer points to Task1
	TaskList[i].elapsedTime = 0;
	i++;

	// TASK 2 - PERIOD & FUNCTION
	TaskList[i].period = 500;
	TaskList[i].TaskPtr = &Task2;
	TaskList[i].elapsedTime = 0;
	i++;

	// TASK 3 - PERIOD & FUNCTION
	TaskList[i].period = 2000;
	TaskList[i].TaskPtr = &Task3;
	TaskList[i].elapsedTime = 0;

	// INITIALIZE SYSTEM TIMER AND GPIO

	initGPIO();
	initSysTick(16000000 / 1000);	//set a 1 ms tick at 16MHz


	while(1){

		scheduler();

	}


}
