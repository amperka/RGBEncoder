#include "RGBEncoder.h"

RGBEncoder knob;

const byte stepPin = A4;
const byte directionPin = A3;
const byte enablePin = 11;

int delayTime = 10;

void stepLeft() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(enablePin, HIGH);
        digitalWrite(directionPin, LOW);
        digitalWrite(stepPin, HIGH);
        delay(delayTime);
        digitalWrite(stepPin, LOW);
        delay(delayTime);
        analogWrite(enablePin, 50);
    }
}

void stepRight() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(enablePin, HIGH);
        digitalWrite(directionPin, HIGH);
        digitalWrite(stepPin, HIGH);
        delay(delayTime);
        digitalWrite(stepPin, LOW);
        delay(delayTime);
        analogWrite(enablePin, 50);
    }
}

void setup() {
    knob.begin();
    knob.onStepLeft(stepLeft);
    knob.onStepRight(stepRight);

    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
}

void loop() {
    knob.update();
}