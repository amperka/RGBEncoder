#include "RGBEncoder.h"

RGBEncoder knob;

void buttonHandler(bool state) {
    if (state) {
        knob.setColor(255, 255, 255);
    } else {
        knob.setColor(0, 0, 0);
    }
}

void setup() {
    knob.begin();
    knob.onButton(buttonHandler);
    knob.setColor(0, 0, 0);
}

void loop() {
    knob.update();
}
