# s32k312mini-eve-BSP
This repository contains a board support package (BSP) for the s32k312mini-eve board.

## Architecture

graph TD
    %% Layer Styles
    classDef l2 fill:#d4edda,stroke:#28a745,stroke-width:2px,color:#155724;
    classDef l1 fill:#cce5ff,stroke:#004085,stroke-width:2px,color:#004085;
    classDef l0 fill:#f8d7da,stroke:#721c24,stroke-width:2px,color:#721c24;

    %% Architecture Flow
    subgraph L2 [Layer 2: Application Layer]
        App["C ANSI Main Program & Logic"]
    end
    
    subgraph L1 [Layer 1: Peripheral Libraries]
        GPIO["GPIO Library"]
        PIT["PIT_TIMER Library"]
    end
    
    subgraph L0 [Layer 0: Hardware Layer]
        S32K["S32K312 Base Lib (MCAL / Registers)"]
    end

    App --> GPIO
    App --> PIT
    GPIO --> S32K
    PIT --> S32K

    class App l2;
    class GPIO,PIT l1;
    class S32K l0;




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