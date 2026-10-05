#include "S32K312.h"
#include "HAL/UART.h"
#include "Libraries/buffer.h"
#include "Libraries/gps/gps_parser.h"

#define BUFFER_SIZE 256

volatile unsigned char buffer_raw_data[BUFFER_SIZE];
volatile char_buffer_t buffer = { 0 };
volatile GPS_Result gps_result = { 0 };

void gpsUARTCallback(char c)
{
	if(!bufferIsFull(&buffer))
	{
		bufferWrite(&buffer, c);
	}
}

char readGPSBuffer(void)
{
	if(bufferIsEmpty(&buffer))
	{
		return NULL;
	}

	unsigned char c;
	char result = bufferRead(&buffer, &c);

	return result ? c : NULL;
}

int main (void)
{
	// Initialize modules
	initUART1(); // Init USB Main UART
	initUART2(); // Init GPS UART
	bufferInit(&buffer, buffer_raw_data, BUFFER_SIZE);

	// Set Interrupt for GPS UART
	setInterruptCallbackRXUART2(gpsUARTCallback);

	while(1)
	{
		gps_result = parseGPS(readGPSBuffer, GPRMC);
		uart1_SendString("GPS Status: ");
		uart1_SendString(gps_result.success ? "OK" : "ERROR");
	}

	return 0;
}
