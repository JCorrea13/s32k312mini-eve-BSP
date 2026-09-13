/**
 * @file GPIO.h
 * @brief Public interface to use the GPIO on the S32K312MINI-EVB.
 */

#if !defined(GIPIO_)
#define GIPIO_

#include "S32K312_UTILS.h"

typedef void (*InputInterruptCallback)(void);

// Red Led Functions
/**
 * Initializes the red led.
 */
void initRedLed(void);

/**
 * Turn on the red led.
 */
void turnOnRedLed(void);

/**
 * Turn off the red led.
 */
void turnOffRedLed(void);

/**
 * Toggle the red led.
 */
void toggleRedLed(void);

// Green Led Functions
/**
 * Initializes the Green led.
 */
void initGreenLed(void);

/**
 * Turn on the Green led.
 */
void turnOnGreenLed(void);

/**
 * Turn off the Green led.
 */
void turnOffGreenLed(void);

/**
 * Toggle the Green led.
 */
void toggleGreenLed(void);

// Blue Led Functions
/**
 * Initializes the Blue led.
 */
void initBlueLed(void);

/**
 * Turn on the Blue led.
 */
void turnOnBlueLed(void);

/**
 * Turn off the Blue led.
 */
void turnOffBlueLed(void);

/**
 * Toggle the Blue led.
 */
void toggleBlueLed(void);

//Input PTB29 Functions
/**
 * Initializes the PTB26 pin as input.
 */
void initInputPTB26(void);

/**
 * Set's an interrupt callback for the input.
 * @param callback function pointer to the callback function that will when the input interruption happens.
 */
void setInterruptCallbackForInputPTB26(InputInterruptCallback callback);

/**
 * Read the current state of the PTB26 pin.
 * @return An uint8_t representing if the pin state is HIGH or LOW.
 * @retval 1 the state is HIGH (Button is pressed)
 * @retval 0 the state is LOW  (Button is NOT pressed)
 */
uint8_t readInputPTB26(void);

//Input PTB19 Functions
/**
 * Initializes the PTB19 pin as input.
 */
void initInputPTB19(void);

/**
 * Read the current state of the PTB19 pin.
 * @return An uint8_t representing if the pin state is HIGH or LOW.
 * @retval 1 the state is HIGH (Button is pressed)
 * @retval 0 the state is LOW  (Button is NOT pressed)
 */
uint8_t readInputPTB19(void);

#endif
