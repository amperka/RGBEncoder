/*
* This example demonstrates pseudo-asynchronous operation with the RGBEncoder button.
* The Knob lights up when the button is pressed.
*/

// Include library
#include "RGBEncoder.h"

// Create object of RGBEncoder
RGBEncoder knob;

// Button handler
void buttonHandler(bool state) {
    if (state) { // if pressed
        knob.setColor(255, 255, 255); // switch-on light
    } else { // if not pressed
        knob.setColor(0, 0, 0); // switch-off light
    }
}

void setup() {
    knob.begin(); // initialization
    knob.onButton(buttonHandler); // connect button handler
    knob.setColor(0, 0, 0); // switch-off light
}

void loop() {
    knob.update(); // it implements pseudo-asynchronous work
}
