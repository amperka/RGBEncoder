#include "RGBEncoder.h"

RGBEncoder knob;

#define CHANGE_RED 0
#define CHANGE_GREEN 1
#define CHANGE_BLUE 2
byte mode = CHANGE_RED;

byte r = 0, g = 0, b = 0;

void buttonHandler(bool state) {
    if (state) {
        switch (mode) {
        case CHANGE_RED:
            mode = CHANGE_GREEN;
            b = knob.getEncoderValue();
            knob.setValue(r);
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

void encoderHandler(int32_t value) {
    switch (mode) {
    case CHANGE_RED:
        r = value;
        break;
    case CHANGE_GREEN:
        g = value;
        break;
    case CHANGE_BLUE:
        b = value;
        break;
    }
    knob.setColor(r, g, b);
}

void setup() {
    knob.begin();
    knob.onButton(buttonHandler);
    knob.onEncoder(encoderHandler);
    knob.setColor(0, 0, 0);
}

void loop() {
    knob.update();
}
