#include "UART.h"
#include "S32K312.h"
#include "core_cm7.h"
#include "S32K312_UTILS.h"

static RXInterruptCallback rx1Callback = NULL;
static RXInterruptCallback rx2Callback = NULL;

void initUART1(void)
{
	// Configure RXTX pins
	IP_SIUL2->MSCR[16] = SIUL2_MSCR_SSS(5)| SIUL2_MSCR_OBE_MASK;
	IP_SIUL2->MSCR[15]= SIUL2_MSCR_SSS(1) + SIUL2_MSCR_IBE_MASK;
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

void uart1_SendChar(char c)
{
	// Wait until there is room in the RX FIFO to write another char
	while(!(IP_LPUART_6->STAT & LPUART_STAT_TDRE_MASK));

	IP_LPUART_6->DATA = c;
}

void uart1_SendString(const char *s)
{
	while(*s)
	{
		uart1_SendChar(*s++);
	}
}

char uart1_GetChar()
{
	// Block until there is something to read
	while(!(IP_LPUART_6->STAT & LPUART_STAT_RDRF_MASK));

	return (char)IP_LPUART_6->DATA;
}

#define __INTERRUPT_LPUART6  __attribute__ ((interrupt ("LPUART6")))
__INTERRUPT_LPUART6 void LPUART6_Handler(void)
{
	if(rx1Callback != NULL)
	{
		rx1Callback((char)IP_LPUART_6->DATA);
	}
}

void setInterruptCallbackRXUART1(RXInterruptCallback callback)
{
	rx1Callback = callback;
	IP_LPUART_6->CTRL |= LPUART_CTRL_RIE(1);
	NVIC_EnableIRQ(LPUART6_IRQn);
}

void initUART2(void)
{
	// Configure RXTX pins
	IP_SIUL2->MSCR[3]= SIUL2_MSCR_SSS(6) + SIUL2_MSCR_IBE_MASK; // TX

	IP_SIUL2->MSCR[2] = SIUL2_MSCR_SSS(3)| SIUL2_MSCR_OBE_MASK; // RX
	IP_SIUL2->IMCR[699-512] = SIUL2_MSCR_SSS(1);

	IP_LPUART_0->CTRL = 0; //Disable RXTX

	/**
	 * Configurar baudrate
         Default: FIRC 48 MHZ, DIV=2
         Clock UART =  24 MHz
         Baud = 115200
         SBR = 24MHz/(16*115200)=13.02
	 */
	// TODO: Make baud rate configurable
	IP_LPUART_0->BAUD =LPUART_BAUD_OSR(15) | LPUART_BAUD_SBR(13);

	IP_LPUART_0->CTRL |= LPUART_CTRL_TE(1)+LPUART_CTRL_RE(1); // Enable RXTX
}

void uart2_SendChar(char c)
{
	// Wait until there is room in the RX FIFO to write another char
	while(!(IP_LPUART_0->STAT & LPUART_STAT_TDRE_MASK));

	IP_LPUART_0->DATA = c;
}

void uart2_SendString(const char *s)
{
	while(*s)
	{
		uart1_SendChar(*s++);
	}
}

char uart2_GetChar()
{
	// Block until there is something to read
	while(!(IP_LPUART_0->STAT & LPUART_STAT_RDRF_MASK));

	return (char)IP_LPUART_0->DATA;
}

#define __INTERRUPT_LPUART0  __attribute__ ((interrupt ("LPUART6")))
__INTERRUPT_LPUART0 void LPUART0_Handler(void)
{
	if(rx2Callback != NULL)
	{
		rx2Callback((char)IP_LPUART_0->DATA);
	}
}

void setInterruptCallbackRXUART2(RXInterruptCallback callback)
{
	rx2Callback = callback;
	IP_LPUART_0->CTRL |= LPUART_CTRL_RIE(1);
	NVIC_EnableIRQ(LPUART0_IRQn);
}
