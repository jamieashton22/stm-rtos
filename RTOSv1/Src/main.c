

// NOTES
// 02/10/25 - setting up a timebase with systick (1 ms). by default cpu uses HSI which is 16MHz, can
// use other ones to get higher clock speeds e.g PLL up to 84 MHz, do this later.

#include <stdint.h>
#include "stm32f401xe.h"
#include "core_cm4.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


// POINTERS TO MEM ADDRESSES --------------------------------------------------------------------


#define SYST_CSR (*(volatile uint32_t*) 0xE000E010)	//systick control and status register
#define SYST_RVR (*(volatile uint32_t*) 0xE000E014)	// reload value register
#define SYST_CVR (*(volatile uint32_t*) 0xE000E018)		// current val register, write any value to clear

// FUNCTION PROTOTYPES and NECESSARY VARIABLES----------------------------------------------------------------------------------------------------------------------------------------

void SysTick_Handler(void);
void initGPIO(void);
void initSysTick(uint32_t time_base);
void blockingDelay_ms(uint32_t delay_time);


volatile uint32_t systick_ms = 0;		// holds elapsed ms


// FUNCTIONS ----------------------------------------------------------------------------------------------------------------------------------------

void initGPIO(void){


	// First enable GPIO clock for port A
	//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// |= is bitwise OR, compares bits and sets if either is 1
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	//GPIOAEN is a bit-mask that sets bit 0 to 1

	// or more bare metal, 1U is just integer '1', U means unsigned INT
	RCC->AHB1ENR |= (1U << 0);		// then we're shifting it 0 places because we want to write 1 to bit 0

	//Now set pin 5 as output
	// first clear the value in pin 10 and 11 by writing 11 to it then negating
	GPIOA->MODER &= ~(3U << 10);
	// shift decimal 3 (b11) 10 places to set bits 10 and 11 as b11, then negate it, then AND it.
	// this preserves the value of all other bits in the register but clears bits 10 and 11 ready to be set.

	GPIOA->MODER |=(1U << 10); // then set bit 10 to 1, so MODE5 is now 01 which sets PA_5 as an output

}

void initSysTick(uint32_t time_base){

	SYST_RVR = time_base - 1; // load tick time into RVR
	SYST_CVR = 0;			// write value to CVR to clear it
	SYST_CSR = (1U << 0) | (1U << 1) | (1U << 2);	// enable, tick-int and clk-source set

}

void SysTick_Handler(void){

	systick_ms++;		// each time interrupt triggered by systick (every ms) increment counter

}

void blockingDelay_ms(uint32_t delay_time){

	uint32_t start_time = systick_ms;

	while(systick_ms - start_time < delay_time){

	}

}

int main(void)
{
	initGPIO();
	initSysTick(16000000 / 1000);	//set a 1 ms tick at 16MHz

	while(1){

		GPIOA->ODR ^= (1U << 5);	// toggle LED
		blockingDelay_ms(1000);

	}
}
