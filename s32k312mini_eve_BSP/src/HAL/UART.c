#include "UART.h"
#include "S32K312.h"
#include "core_cm7.h"
#include "S32K312_UTILS.h"

static RXInterruptCallback rxCallback = NULL;

void initUART(void)
{
	// Configure RXTX pins
	IP_SIUL2->MSCR[16] = SIUL2_MSCR_SSS(5)| SIUL2_MSCR_OBE_MASK;
	IP_SIUL2->MSCR[15]= 1 + SIUL2_MSCR_IBE_MASK;
	IP_SIUL2->IMCR[705-512] = SIUL2_MSCR_SSS(2);

	// Get out of Power Down
	// TODO: move to it's own module
	IP_MC_ME->PRTN1_COFB2_CLKEN |= MC_ME_PRTN1_COFB2_CLKEN_REQ80(1);
	IP_MC_ME->PRTN1_PUPD = 1;
	IP_MC_ME->CTL_KEY = 0x5AF0;
	IP_MC_ME->CTL_KEY = 0xA50F;

	while (IP_MC_ME->PRTN0_PUPD)
	{
		//TODO: define a timeout
	}

	IP_LPUART_6->CTRL = 0; //Disable RXTX

	/**
	 * Configurar baudrate
         Default: FIRC 48 MHZ, DIV=2
         Clock UART =  24 MHz
         Baud = 115200
         SBR = 24MHz/(16*115200)=13.02
	 */
	// TODO: Make baud rate configurable
	IP_LPUART_6->BAUD =LPUART_BAUD_OSR(15) | LPUART_BAUD_SBR(13);

	IP_LPUART_6->CTRL |= LPUART_CTRL_TE(1)+LPUART_CTRL_RE(1); // Enable RXTX
}

void uart_SendChar(char c)
{
	// Wait until there is room in the RX FIFO to write another char
	while(!(IP_LPUART_6->STAT & LPUART_STAT_TDRE_MASK));

	IP_LPUART_6->DATA = c;
}

void uart_SendString(const char *s)
{
	while(*s)
	{
		uart_SendChar(*s++);
	}
}

char uart_GetChar()
{
	// Block until there is something to read
	while(!(IP_LPUART_6->STAT & LPUART_STAT_RDRF_MASK));

	return (char)IP_LPUART_6->DATA;
}

#define __INTERRUPT_LPUART6  __attribute__ ((interrupt ("LPUART6")))
__INTERRUPT_LPUART6 void LPUART6_Handler(void)
{
	if(rxCallback != NULL)
	{
		rxCallback((char)IP_LPUART_6->DATA);
	}
}

void setInterruptCallbackRXUART(RXInterruptCallback callback)
{
	rxCallback = callback;
	IP_LPUART_6->CTRL |= LPUART_CTRL_RIE(1);
	NVIC_EnableIRQ(LPUART6_IRQn);
}

