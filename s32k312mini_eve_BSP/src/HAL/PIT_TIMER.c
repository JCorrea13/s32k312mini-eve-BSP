#include "PIT_TIMER.h"
#include "S32K312.h"
#include "core_cm7.h"

#define PIT_CLOCK	48000000UL

static TimerInterruptCallback PIT0Titmer1Callback = NULL;

void initTimer(void)
{
	IP_PIT_0->MCR = 0; // Enable Timer
}

void delay(uint32_t ms)
{
	IP_PIT_0->TIMER[0].LDVAL =(PIT_CLOCK / 1000UL) * ms - 1UL; // Set period
	IP_PIT_0->TIMER[0].TCTRL = PIT_TCTRL_TEN(1); // Start the timer

	while(!(IP_PIT_0->TIMER[0].TFLG & PIT_TFLG_TIF_MASK)); // Blocking Delay

	IP_PIT_0->TIMER[0].TFLG = PIT_TFLG_TIF_MASK; // Clean Flag
}

void setInterruptCallbackForTimer(uint32_t ms, TimerInterruptCallback callback)
{
	IP_PIT_0->TIMER[1].LDVAL = (PIT_CLOCK / 1000UL) * ms - 1UL; // Set period

	PIT0Titmer1Callback = callback; // Assign Interrupt Callback

	// Enable the PIT interrupt and start the timer
	IP_PIT_0->TIMER[1].TCTRL = PIT_TCTRL_TEN(1)+ PIT_TCTRL_TIE(1);
	NVIC_EnableIRQ(PIT0_IRQn); // Enable the interrupt in the NVIC
}

#define __INTERRUPT_PIT0  __attribute__ ((interrupt ("PIT0")))
__INTERRUPT_PIT0 void PIT0_Handler(void)
{
    IP_PIT_0->TIMER[1].TFLG = PIT_TFLG_TIF_MASK;	//Clear flag

    if (PIT0Titmer1Callback != NULL)
    {
    	PIT0Titmer1Callback();
    }
}
