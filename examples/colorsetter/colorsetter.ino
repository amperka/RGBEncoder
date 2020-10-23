/*
* The example demonstrates the operation of all RGBEncoder inner devices.
* The encoder adjusts the RGB color components one by one. 
* The button selects which color component is adjusted.
* The LED displays the selected color.
*/

// Include library
#include "RGBEncoder.h"

// Create an RGBEncoder object
RGBEncoder knob;

// mode is the state of a finite-state machine.
// By switching these states, we select the color component that we want to adjust.
#define CHANGE_RED 0
#define CHANGE_GREEN 1
#define CHANGE_BLUE 2
byte mode = CHANGE_RED;

// Current color components values
byte red = 0, green = 0, blue = 0;

// Handler of button
void buttonHandler(bool state) {
    if (state) { // if button pressed ...
        switch (mode) {
        case CHANGE_RED:
            mode = CHANGE_GREEN; // select next state
            blue = knob.getEncoderValue(); // save previous color component value
            knob.setValue(red); // load new color component value
            break;
        case CHANGE_GREEN:
            mode = CHANGE_BLUE;
            red = knob.getEncoderValue();
            knob.setValue(green);
            break;
        case CHANGE_BLUE:
            mode = CHANGE_RED;
            green = knob.getEncoderValue();
            knob.setValue(blue);
            break;
        }
    }
}

// Handler of encoder
void encoderHandler(int32_t value) {
    switch (mode) {
    case CHANGE_RED:
        red = value; // load new value to color component
        break;
    case CHANGE_GREEN:
        green = value;
        break;
    case CHANGE_BLUE:
        blue = value;
        break;
    }
    knob.setColor(red, green, blue); // show new color
}

void setup() {
    knob.begin(); // initialization
    // register handlers for button and encoder
    knob.onButton(buttonHandler);
    knob.onEncoder(encoderHandler);
    // switch-off led
    knob.setColor(0, 0, 0);
}

void loop() {
    knob.update(); // it implements pseudo-asynchronous work
}
