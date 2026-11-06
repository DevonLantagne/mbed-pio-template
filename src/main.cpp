/*
This blinky program uses OS timer interrupts for stable blink rates.

The onboard button is used to enable and disable the LED blink system.

*/

#include "mbed.h"

// Application Constants
// "constexpr" is the modern replacement for #define constants
constexpr uint32_t MAIN_EXEC_RATE_HZ    = 1000; // main background loop rate
constexpr uint32_t LED_TOGGLE_PERIOD_MS = 250;  // led blink period (milliseconds)

constexpr uint32_t LED_TOGGLE_COUNTS = 
    (LED_TOGGLE_PERIOD_MS * MAIN_EXEC_RATE_HZ) / 1000;

// Hardware Pin Assignments
#define PIN_LED         LED1        // Nucleo assigns LED1 to pin D13 (onboard LED)
#define PIN_BUTTON      BUTTON1     // Nucleo built-in button (soldered pull-up)

// Operating System Variables (Hardware Interfaces)
// AnalogIn, DigitalOut, PwmOut, BusOut, etc. objects here
Ticker backgroundTrk;               // Periodic timer interrupt for main loop
DigitalOut led(PIN_LED);            // onboard led
InterruptIn btn(PIN_BUTTON, PullNone); // use soldered pull-up

// Global Variables
volatile bool doBackground = false; // ISR flag
volatile bool enableLED = true;     // Flag to control if LED should blink

// Function Prototypes
void backgroundISR();
void btnISR();

int main()
{
    // Setup Section

    // Set up any digital IO (pullup/pulldown resistors) or PWM period.


    // Create Variables Here
    uint32_t counter = 0;


    // Other One-Time code:
    led.write(0); // init LED off
    // Start ticker timer interrupt system
    backgroundTrk.attach(
        &backgroundISR, 
        1.0/MAIN_EXEC_RATE_HZ
    );
    // Enable the button interrupt system
    btn.fall(&btnISR); // falling edge is first event for pull-up


    // Main Loop Section (background task)
    // Only executes code when ISR tells us to.
    while (true)
    {
        if (doBackground){

            // Read inputs here



            // Main code logic here and control outputs

            if (enableLED){
                counter++;
                if (counter > LED_TOGGLE_COUNTS){
                    led.write(!led.read()); // toggle
                    counter = 0; // reset
                }
            }
            
            doBackground = false; // clear the flag
        }
    }
}


// ISRs

void backgroundISR(){
    if (doBackground){
        // If the flag is already set, the main loop is OVERLOADED!!!
        // Execute recovery plan or build a better system

    }

    // Flag main to execute loop
    doBackground = true;
}

void btnISR(){
    enableLED = !enableLED; // toggle LED mode
}