#include "RGBEncoder.h"

RGBEncoder knob;

bool light = false;
uint32_t ms = 0;

void setup() {
    knob.begin();
    knob.setRange(1, 30);
    knob.setValue(1);
    knob.setColor(0, 0, 0);
    ms = millis() + 500 / (knob.getEncoderValue());
}

void loop() {
    knob.update();
    if (millis() > ms) {
        ms = millis() + 500 / (knob.getEncoderValue());
        if (light) {
            light = false;
            knob.setColor(0, 0, 0);
        } else {
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
