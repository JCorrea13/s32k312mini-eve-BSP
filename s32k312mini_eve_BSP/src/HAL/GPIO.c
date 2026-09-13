#include "S32K312.h"
#include "S32K312_UTILS.h"
#include "core_cm7.h"
#include "GPIO.h"

static InputInterruptCallback PTB26InputCallbackFunction = NULL;

// Red Led Functions
void initRedLed(void)
{
	IP_SIUL2->MSCR[29] = SIUL2_MSCR_OBE(1) | SIUL2_MSCR_SSS(0);
}

void turnOnRedLed(void)
{
	IP_SIUL2->GPDO29 = 0U;
}

void turnOffRedLed(void)
{
	IP_SIUL2->GPDO29 = 1U;
}

void toggleRedLed(void)
{
	IP_SIUL2->GPDO29 ^= 1U;
}

// Green Led Functions
void initGreenLed(void)
{
	IP_SIUL2->MSCR[30] = SIUL2_MSCR_OBE(1) | SIUL2_MSCR_SSS(0);
}

void turnOnGreenLed(void)
{
	IP_SIUL2->GPDO30 = 0U;
}

void turnOffGreenLed(void)
{
	IP_SIUL2->GPDO30 = 1U;
}

void toggleGreenLed(void)
{
	IP_SIUL2->GPDO30 ^= 1U;
}

// Blue Led Functions
void initBlueLed(void)
{
	IP_SIUL2->MSCR[31] = SIUL2_MSCR_OBE(1) | SIUL2_MSCR_SSS(0);
}

void turnOnBlueLed(void)
{
	IP_SIUL2->GPDO31 = 0U;
}

void turnOffBlueLed(void)
{
	IP_SIUL2->GPDO31 = 1U;
}

void toggleBlueLed(void)
{
	IP_SIUL2->GPDO31 ^= 1U;
}

//Input PTB29 Functions
void initInputPTB26(void)
{
	IP_SIUL2->MSCR[58] = SIUL2_MSCR_IBE(1)| SIUL2_MSCR_SSS(0);
}

#define __INTERRUPT_SIUL_1  __attribute__ ((interrupt ("SIUL1")))
__INTERRUPT_SIUL_1 void SIUL_1_Handler(void)
{
    if ((IP_SIUL2->DISR0 & SIUL2_DISR0_EIF13_MASK) != 0U)		//External Interrupt Flag
    {
        if(PTB26InputCallbackFunction != NULL)
        {
        	PTB26InputCallbackFunction();
        }

        IP_SIUL2->DISR0 = SIUL2_DISR0_EIF13_MASK; // Clean flag
    }
}

void setInterruptCallbackForInputPTB26(InputInterruptCallback callback)
{
	IP_SIUL2->IMCR[541-512] = SIUL2_MSCR_SSS(2);	// Excel EIRQ 13
	IP_SIUL2->IREER0 &= ~SIUL2_IREER0_IREE13_MASK;	//Deshabilita rising edge
	IP_SIUL2->IFEER0 |=SIUL2_IFEER0_IFEE13_MASK;	//Habilita falling edge
	IP_SIUL2->DIRSR0 &= ~SIUL2_DIRSR0_DIRSR13_MASK;	//Selecciona IRQ, no DMA request
	IP_SIUL2->DISR0 = SIUL2_DISR0_EIF13_MASK;		//Limpia bandera pendiente
	IP_SIUL2->DIRER0 |=SIUL2_DIRER0_EIRE13_MASK;	//Habilita EIRQ 13

	PTB26InputCallbackFunction =  callback;			// Assign Callback

	NVIC_EnableIRQ(SIUL_1_IRQn);					//Page 306 Reference Manual
	__enable_irq();									//NVIC: Nested Vector Interrupt Controller
}

uint8_t readInputPTB26(void)
{
	return IP_SIUL2->GPDI58 == 0U;
}

//Input PTB19 Functions
void initInputPTB19(void)
{
	IP_SIUL2->MSCR[51] = SIUL2_MSCR_IBE(1)| SIUL2_MSCR_SSS(0);
}

uint8_t readInputPTB19(void)
{
	return IP_SIUL2->GPDI51 == 0U;
}

