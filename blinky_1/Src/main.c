

#include <stdint.h>
#include "stm32f401xe.h"
#include "core_cm4.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


// POINTERS TO MEM ADDRESSES
#define SYST_CSR (*(volatile uint32_t*) 0xE000E010)	//systick control and status register
#define SYST_RVR (*(volatile uint32_t*) 0xE000E014)	// reload value register
#define SYST_CVR (*(volatile uint32_t*) 0xE000E018)		// current val register, write any value to clear

void SysTick_Handler(void);
void delay(volatile uint32_t count); // function to delay
void initGPIO(void);
void initSYSTICK(void);

void delay(volatile uint32_t count){
	// parameter is volatile because tells compiler not to optimise this variable,
	// without it the compiler will see that the loop does nothing and may get rid of it

	while(count--){	// decrement count on each iteration of the loop
		__asm__("nop");
	}		//simple crude wait

}

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

void initSysTick(void){

	SYST_RVR = 16000000 - 1; // 1 second for 16MHz
	SYST_CVR = 0;			// write value to CVR to clear it
	SYST_CSR = (1U << 0) | (1U << 1) | (1U << 2);	// enable, tick-int and clk-source set

}

void SysTick_Handler(void){

	GPIOA->ODR ^= (1U << 5);	//xor - toggles LED

}

int main(void)
{
	initGPIO();
	initSysTick();

}
