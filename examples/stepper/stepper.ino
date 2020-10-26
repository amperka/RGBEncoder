/*
* This example demonstrates the use of RGBEncoder to control a stepper motor.
*/

// Include library
#include "RGBEncoder.h"

// Create object of RGBEncoder
RGBEncoder knob;

// Assigning the motor driver control pins
const byte stepPin = A4;
const byte directionPin = A3;
const byte enablePin = 11;

// Time to step with the motor
int delayTime = 10;

// Handler. Called when the encoder is turned left
void stepLeft() {
    for (int i = 0; i < 5; i++) { // 5 motor steps on 1 encoder step
        digitalWrite(enablePin, HIGH);
        digitalWrite(directionPin, LOW);
        digitalWrite(stepPin, HIGH);
        delay(delayTime);
        digitalWrite(stepPin, LOW);
        delay(delayTime);
        analogWrite(enablePin, 50);
    }
}

// Handler. Called when the encoder is turned right
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
    knob.begin(); // initialisation
    // Register on-step handlers
    knob.onStepLeft(stepLeft);
    knob.onStepRight(stepRight);

    // Motor driver GPIO initialisation
    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
}

void loop() {
    knob.update(); // upkeep to trigger the handler when necessary
}
