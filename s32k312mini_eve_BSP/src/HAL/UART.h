/**
 * @file UART.h
 * @brief Public interface to use the UART on the S32K312MINI-EVB.
 */

#if !defined(UART_)
#define UART_

typedef void (*RXInterruptCallback)(char c);

/**
 * Initialize the UART.
 */
void initUART(void);

/**
 * Sends a chart over UART
 * @param c the char to be sent.
 */
void uart_SendChar(char c);

/**
 * Sends a string over UART
 * @param c pointer to a the first char of the string to be sent.
 */
void uart_SendString(const char *c);

/**
 * Blocking read char from UART.
 * @return the read char from the UART.
 */
char uart_GetChar();

/**
 * Set's a callback function that will be called when there is DATA in the UART Receiver.
 * @param callback the function to be called by the interrupt
 */
void setInterruptCallbackRXUART(RXInterruptCallback callback);

#endif
