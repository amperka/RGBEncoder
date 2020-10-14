/*
 * This file is a part of RGBEncoder library.
 *
 * Product page: https://amperka.ru/product/rgbencoder
 * © Amperka LLC (https://amperka.com, dev@amperka.com)
 *
 * Author: Yury Botov <by@amperka.com>
 * License: GPLv3, all text here must be included in any redistribution.
 */

#include "RGBEncoder.h"

void buttonDumb(bool state) { (void)state; }
void encoderDumb(int32_t value) { (void)value; }
void stepsDumb() { }

RGBEncoder::RGBEncoder(uint8_t i2cAddress) {
    _i2cAddress = i2cAddress;
    _buttonState = false;
    _encoderLowerBound = 0;
    _encoderUpperBound = 255;
    _encoderCurrentValue = 0;
    _encoderStep = 1;
    _encoderMode = RGBENC_CLAMP;
    _buttonHandler = buttonDumb;
    _encoderHandler = encoderDumb;
    _stepLeftHandler = stepsDumb;
    _stepRightHandler = stepsDumb;
}

void RGBEncoder::begin() { begin(&Wire); }

void RGBEncoder::begin(TwoWire* wire) {
    wire->begin();
    GpioExpander::begin(wire);

    GpioExpander::pinMode(_redLedPin, OUTPUT);
    GpioExpander::analogWrite(_redLedPin, 0);
    GpioExpander::pinMode(_greenLedPin, OUTPUT);
    GpioExpander::analogWrite(_greenLedPin, 0);
    GpioExpander::pinMode(_blueLedPin, OUTPUT);
    GpioExpander::analogWrite(_blueLedPin, 0);

    GpioExpander::pinMode(_encoderAPin, INPUT);
    GpioExpander::pinMode(_encoderBPin, INPUT);
    GpioExpander::setEncoderPins(0, _encoderAPin, _encoderBPin);

    GpioExpander::pinMode(_buttonPin, INPUT);
    int16_t state = GpioExpander::digitalRead(_buttonPin);
    if (state == 0)
        _buttonState = false;
    else
        _buttonState = true;
}

void RGBEncoder::changeAddr(uint8_t newAddress) {
    GpioExpander::changeAddr(newAddress);
}

void RGBEncoder::saveAddr() {
    GpioExpander::saveAddr();
}

void RGBEncoder::setValue(int32_t value) { _encoderCurrentValue = value; }

void RGBEncoder::setRange(int32_t min, int32_t max) {
    _encoderLowerBound = min;
    _encoderUpperBound = max;
}

void RGBEncoder::setStep(int32_t step) { _encoderStep = step; }

void RGBEncoder::setMode(enum EncoderMode mode) { _encoderMode = mode; }

void RGBEncoder::update() {
    // button part
    int16_t state = GpioExpander::digitalRead(_buttonPin);
    if (state == LOW && _buttonState) {
        delay(_debounceTime);
        state = GpioExpander::digitalRead(_buttonPin);
        if (state == LOW) {
            _buttonState = false;
            _buttonHandler(false);
        }
    }
    if (state != 0 && _buttonState == false) {
        delay(_debounceTime);
        state = GpioExpander::digitalRead(_buttonPin);
        if (state != 0) {
            _buttonState = true;
            _buttonHandler(true);
        }
    }
    // encoder part
    int8_t difference = readEncoderDiff(0);
    if (difference != 0) {
        if (difference > 0) { // left
            for (int i = 0; i < difference; i++)
                _stepLeftHandler();
        } else if (difference < 0) { // right
            for (int i = 0; i < -difference; i++)
                _stepRightHandler();
        }

        _encoderCurrentValue += difference * _encoderStep;
        if (_encoderMode == RGBENC_WRAP) {
            if (_encoderCurrentValue > _encoderUpperBound) {
                _encoderCurrentValue = _encoderLowerBound + (_encoderCurrentValue - _encoderUpperBound);
            }
            if (_encoderCurrentValue < _encoderLowerBound) {
                _encoderCurrentValue = _encoderUpperBound - (_encoderCurrentValue - _encoderLowerBound);
            }
        } else { // if RGBENC_CLAMP
            if (_encoderCurrentValue > _encoderUpperBound) {
                _encoderCurrentValue = _encoderUpperBound;
            }
            if (_encoderCurrentValue < _encoderLowerBound) {
                _encoderCurrentValue = _encoderLowerBound;
            }
        }
        _encoderHandler(_encoderCurrentValue);
    }
}

void RGBEncoder::setColor(uint8_t r, uint8_t g, uint8_t b) {
    GpioExpander::analogWrite(_redLedPin, 255 - r);
    GpioExpander::analogWrite(_greenLedPin, 255 - g);
    GpioExpander::analogWrite(_blueLedPin, 255 - b);
}

bool RGBEncoder::isButtonPressed() const { return _buttonState; }

int32_t RGBEncoder::getEncoderValue() const { return _encoderCurrentValue; }

void RGBEncoder::onButton(void (*buttonHandler)(bool state)) { _buttonHandler = buttonHandler; }

void RGBEncoder::onEncoder(void (*encoderHandler)(int32_t value)) { _encoderHandler = encoderHandler; }

void RGBEncoder::onStepLeft(void (*handler)()) { _stepLeftHandler = handler; }

void RGBEncoder::onStepRight(void (*handler)()) { _stepRightHandler = handler; }
