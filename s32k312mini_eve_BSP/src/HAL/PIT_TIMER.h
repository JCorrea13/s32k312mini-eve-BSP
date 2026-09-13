/**
 * @file PIT_TIMER.h
 * @brief Public interface to use the PIT Timer module on the S32K312MINI-EVB.
 */

#if !defined(PIT_TIMER_)
#define PIT_TIMER_

#include "typedefs.h"
#include <stddef.h>

/**
 * TimerInterruptCallback is a type to register Timer Interrupt callbacks
 */
typedef void (*TimerInterruptCallback)(void);

/**
 * Initialize the PIT0 Timers.
 */
void initTimer(void);

/**
 * Blocking delay.
 * @param ms time in milliseconds that the timer will block.
 */
void delay(uint32_t ms);

/**
 * Set's an interrupt callback for a timer
 * @param ms time in milliseconds that defines the timer period.
 * @param callback function pointer to the callback function that will be called by the timer.
 */
void setInterruptCallbackForTimer(uint32_t ms, TimerInterruptCallback callback);

#endif
