# s32k312mini-eve-BSP
This repository contains a board support package (BSP) for the s32k312mini-eve board.

## Architecture


# Modules
## PIT TIMER
This module exposes functions to work with the PITO Timers.

| Function                     | Description                                                                                                             | Example                                    |
|------------------------------|-------------------------------------------------------------------------------------------------------------------------|--------------------------------------------|
| initTimer                    | Initialize the PIT0 Timers. This function should be called before using the timer delay or registering an interruption. | initTimer();                               |
| delay                        | Blocking delay.                                                                                                         | delay(100UL);                              |
| setInterruptCallbackForTimer | Set's an interrupt callback for a timer.                                                                                | setInterruptCallbackForTimer(100UL, myFn); |

## GPIO
This module exposes functions to work with the GPIO.

| Function                          | Description                                | Example                                    |
|-----------------------------------|--------------------------------------------|--------------------------------------------|
| initRedLed                        | Initializes the Red led.                   | initRedLed();                              |
| turnOnRedLed                      | Turn on the Red led.                       | turnOffRedLed();                           |
| turnOffRedLed                     | Turn off the Red led.                      | turnOffRedLed();                           |
| toggleRedLed                      | Toggle the Red led.                        | toggleRedLed();                            |
| initGreenLed                      | Initializes the Green led.                 | initGreenLed();                            |
| turnOnGreenLed                    | Turn on the Green led.                     | turnOffGreenLed();                         |
| turnOffGreenLed                   | Turn off the Green led.                    | turnOffGreenLed();                         |
| toggleGreenLed                    | Toggle the Green led.                      | toggleGreenLed();                          |
| initBlueLed                       | Initializes the Blue led.                  | initBlueLed();                             |
| turnOnBlueLed                     | Turn on the Blue led.                      | turnOffBlueLed();                          |
| turnOffBlueLed                    | Turn off the Blue led.                     | turnOffBlueLed();                          |
| toggleBlueLed                     | Toggle the Blue led.                       | toggleBlueLed();                           |
| initInputPTB26                    | Initializes the PTB26 pin as input.        | initInputPTB26();                          |
| setInterruptCallbackForInputPTB26 | Set's an interrupt callback for the input. | setInterruptCallbackForInputPTB26(myFunc); |
| readInputPTB26                    | Read the current state of the PTB26 pin.   | readInputPTB26();                          |
| initInputPTB19                    | Initializes the PTB19 pin as input.        | initInputPTB19();                          |
| readInputPTB19                    | Read the current state of the PTB19 pin.   | readInputPTB19();                          |