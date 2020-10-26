/*
 * This file is a part of RGBEncoder library.
 *
 * Product page: https://amperka.ru/product/troyka-rgb-encoder
 * © Amperka LLC (https://amperka.com, dev@amperka.com)
 * 
 * Author: Yury Botov <by@amperka.com>
 * License: GPLv3, all text here must be included in any redistribution.
 */

#ifndef __RGB_ENCODER_H__
#define __RGB_ENCODER_H__

#include "GpioExpander.h"
#include <Arduino.h>
#include <Wire.h>

enum EncoderMode {
    RGBENC_CLAMP,
    RGBENC_WRAP
};

class RGBEncoder : private GpioExpander {
public:
    RGBEncoder(uint8_t i2cAddress = 42);

    void begin();
    void begin(TwoWire* wire);

    void changeAddr(uint8_t newAddress);
    void saveAddr();

    void setValue(int32_t value);
    void setRange(int32_t min, int32_t max);
    void setStep(int32_t step);
    void setMode(EncoderMode mode);

    void update();

    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    bool isButtonPressed() const;
    int32_t getEncoderValue() const;

    void onButton(void (*buttonHandler)(bool state));
    void onEncoder(void (*encoderHandler)(int32_t value));
    void onStepLeft(void (*handler)());
    void onStepRight(void (*handler)());

private:
    static constexpr uint8_t _redLedPin = 2;
    static constexpr uint8_t _greenLedPin = 1;
    static constexpr uint8_t _blueLedPin = 0;
    static constexpr uint8_t _encoderAPin = 7;
    static constexpr uint8_t _encoderBPin = 8;
    static constexpr uint8_t _buttonPin = 3;
    static constexpr uint16_t _debounceTime = 20; // ms

    uint8_t _i2cAddress;
    bool _buttonState;
    int32_t _encoderLowerBound;
    int32_t _encoderUpperBound;
    int32_t _encoderCurrentValue;
    uint32_t _encoderStep;
    EncoderMode _encoderMode;
    void (*_buttonHandler)(bool);
    void (*_encoderHandler)(int32_t);
    void (*_stepLeftHandler)();
    void (*_stepRightHandler)();
};

#endif // __RGB_ENCODER_H__
