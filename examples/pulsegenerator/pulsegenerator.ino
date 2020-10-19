/*
 * This example demonstrates the operation of an RGBEncoder.
 * This is a square wave generator with a frequency adjustable by an encoder in the range of 1...30 Hz.
 */

// Include library
#include "RGBEncoder.h"

// Create an RGBEncoder object
RGBEncoder knob;

// Knob is light variable
bool light = false;

// Next change of brightness time
uint32_t ms = 0;

void setup() {
    knob.begin();
    knob.setRange(1, 30); // set working frequency range
    knob.setValue(1); // on start - 1 Hz
    knob.setColor(0, 0, 0); // switch-off light
    ms = millis() + 500 / (knob.getEncoderValue()); // set next change time
}

void loop() {
    knob.update(); // update object fields from RGBEncoder

    if (millis() > ms) { // if next change time reached
        ms = millis() + 500 / (knob.getEncoderValue()); // set next change time
        if (light) {
            // switch-off light
            light = false;
            knob.setColor(0, 0, 0);
        } else {
            // switch-on light. Use red color for 1...9 Hz, green for 10...19 Hz, blue for 20...30 Hz
            light = true;
            if (knob.getEncoderValue() < 10)
                knob.setColor(255, 0, 0);
            else if (knob.getEncoderValue() < 20)
                knob.setColor(0, 255, 0);
            else
                knob.setColor(0, 0, 255);
        }
    }
}
