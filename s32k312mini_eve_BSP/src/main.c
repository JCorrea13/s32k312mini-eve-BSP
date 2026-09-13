#include "S32K312.h"

#include "HAL/GPIO.h"
#include "HAL/PIT_TIMER.h"

int main (void)
{
	// Initialize modules
	initRedLed();
	initGreenLed();
	initBlueLed();
	initInputPTB26();
	initInputPTB19();
	initTimer();

	// Set Interrupt Callbacks
	setInterruptCallbackForInputPTB26(toggleGreenLed);
	setInterruptCallbackForTimer(500UL, toggleBlueLed);

	while(1)
	{
		do {} while (!readInputPTB19());
		turnOnRedLed();
		delay(100UL);

		turnOffRedLed();
		delay(100UL);
	}

	return 0;
}
