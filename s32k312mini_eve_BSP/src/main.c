#include "S32K312.h"
#include "HAL/UART.h"

void rxCallback(char c)
{
	uart2_SendChar(c);
}

int main (void)
{
	// Initialize modules
	initUART1();

	// Set Interrupt Callbacks
	setInterruptCallbackRXUART1(rxCallback);

	while(1)
	{

	}

	return 0;
}
