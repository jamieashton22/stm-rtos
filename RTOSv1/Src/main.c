

// NOTES
// 02/10/25 - setting up a timebase with systick (1 ms). by default cpu uses HSI which is 16MHz, can
// use other ones to get higher clock speeds e.g PLL up to 84 MHz, do this later.

#include <stdint.h>
#include "stm32f401xe.h"
#include "core_cm4.h"
#include "scheduler.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

TaskType TaskList[TOTAL_TASKS];	// array to hold tasks

void initGPIO(void);


void initGPIO(void){

	RCC->AHB1ENR |= (1U << 0);				// LED
	GPIOA->MODER &= ~(3U << 10);
	GPIOA->MODER |=(1U << 10);
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
