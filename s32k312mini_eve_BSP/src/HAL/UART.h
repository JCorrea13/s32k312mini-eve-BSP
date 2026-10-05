/**
 * @file UART.h
 * @brief Public interface to use the UART on the S32K312MINI-EVB.
 */

#if !defined(UART_)
#define UART_

typedef void (*RXInterruptCallback)(char c);

/**
 * Initialize the UART 1.
 */
void initUART1(void);

/**
 * Sends a chart over UART 1
 * @param c the char to be sent.
 */
void uart1_SendChar(char c);

/**
 * Sends a string over UART 1
 * @param c pointer to a the first char of the string to be sent.
 */
void uart1_SendString(const char *c);

/**
 * Blocking read char from UART 1.
 * @return the read char from the UART 1.
 */
char uart1_GetChar();

/**
 * Set's a callback function that will be called when there is DATA in the UART 1 Receiver.
 * @param callback the function to be called by the interrupt
 */
void setInterruptCallbackRXUART1(RXInterruptCallback callback);

/**
 * Initialize the UART 2.
 */
void initUART2(void);

/**
 * Sends a chart over UART 2.
 * @param c the char to be sent.
 */
void uart2_SendChar(char c);

/**
 * Sends a string over UART 2.
 * @param c pointer to a the first char of the string to be sent.
 */
void uart2_SendString(const char *c);

/**
 * Blocking read char from UART 2.
 * @return the read char from the UART 2.
 */
char uart2_GetChar();

/**
 * Set's a callback function that will be called when there is DATA in the UART 2 Receiver.
 * @param callback the function to be called by the interrupt
 */
void setInterruptCallbackRXUART2(RXInterruptCallback callback);

#endif
