/*
* The example demonstrates the operation of all RGBEncoder inner devices.
* The encoder adjusts the RGB color components one by one. 
* The button selects which color component is adjusted.
* The LED displays the selected color.
*/

// Include library
#include "RGBEncoder.h"

// Create object of RGBEncoder
RGBEncoder knob;

// mode is the state of a finite-state machine.
// By switching these states, we select the color component that we want to adjust.
#define CHANGE_RED 0
#define CHANGE_GREEN 1
#define CHANGE_BLUE 2
byte mode = CHANGE_RED;

// Current color components values
byte r = 0, g = 0, b = 0;

// Handler of button
void buttonHandler(bool state) {
    if (state) { // if button pressed ...
        switch (mode) {
        case CHANGE_RED:
            mode = CHANGE_GREEN; // select next state
            b = knob.getEncoderValue(); // save previous color component value
            knob.setValue(r); // load new color component value
            break;
        case CHANGE_GREEN:
            mode = CHANGE_BLUE;
            r = knob.getEncoderValue();
            knob.setValue(g);
            break;
        case CHANGE_BLUE:
            mode = CHANGE_RED;
            g = knob.getEncoderValue();
            knob.setValue(b);
            break;
        }
    }
}

// Handler of encoder
void encoderHandler(int32_t value) {
    switch (mode) {
    case CHANGE_RED:
        r = value; // load new value to color component
        break;
    case CHANGE_GREEN:
        g = value;
        break;
    case CHANGE_BLUE:
        b = value;
        break;
    }
    knob.setColor(r, g, b); // show new color
}

void setup() {
    knob.begin(); // initialisation
    // register handlers for button and encoder
    knob.onButton(buttonHandler);
    knob.onEncoder(encoderHandler);
    // switch-of led
    knob.setColor(0, 0, 0);
}

void loop() {
    knob.update(); // it implements pseudo-asynchronous work
}
