# RGBEncoder API

## `class RGBEncoder`

Create an `RGBEncoder` object to work with the multifunctional module [RGBEncoder] (https://my.amperka.com/modules/RGBEncoder).
This module is a rotation encoder, a button (when you press the encoder shaft), and RGB illumination of the encoder shaft. There are two interfaces for the button and encoder: direct access and pseudo-asynchronous.

### `RGBEncoder(uint8_t i2cAddress = 42)`

Creates a new `RGBEncoder` object using hardware i2c.

- `i2cAddress`: i2c bus device address. When called without a parameter, its value is assumed to be 42.


### `void begin()`
### `void begin(TwoWire* wire)`

Initializes the interface, sets the device to the "default" state. In this case, the operating range of the encoder values ​​is set [0-255], the value of the encoder at start is 0, the step of change is 1, the mode is "within the range".
Call this method before interacting with RGBEncoder. For example, in the `setup ()` function.

- `wire`: selected i2c interface. When called without a parameter, the `Wire` hardware interface.

### `void changeAddr(uint8_t newAddress)`

- `newAddress`: new i2c address for device.

### `void saveAddr(void)`

Saves the current device i2c address to EEPROM.

### `void setValue(int32_t value)`

Forces the current value of the encoder. If this value is outside the working range, it is converted to the extreme value of the working range.

- `value`: the set value of the encoder [−2147483648; 2147483647] must be within the range set by the` setRange` command.

### `void setRange(int32_t min, int32_t max)`

Sets the limits of the working range of the encoder values. If the current value is outside the operating range, it is converted to the extreme value of the operating range.

- `min`: lower limit of the encoder working range [−2147483648; 2147483647].
- `max`: upper limit of the encoder working range [−2147483648; 2147483647].

### `void setStep(int32_t step)`

Sets the step of changing the encoder value.

- `step`: step of changing the encoder value.

### `void setMode(enum EncoderMode mode)`

Sets the operation mode of the encoder - with clamp on the range or cyclic.

- `mode`: the set mode of the encoder, can be` RGBENC_CLAMP` or `RGBENC_WRAP`.

### `void update()`

Synchronizes the encoder state. Call it in `loop ()`.

### `void setColor(uint8_t red, uint8_t green, uint8_t blue)`

Sets the color of the encoder shaft illumination based on three color components:

- `red`: [0-255] brightness of the red LED.
- `green`: [0-255] green LED brightness.
- `blue`: [0-255] the brightness of the blue LED.

### `bool isButtonPressed() const`

Returns the current debounced state of the button.

### `int32_t getEncoderValue() const`

Returns the current value of the encoder.

### `void onButton(void (*buttonHandler)(bool state))`

Registers a function - an event handler from a button.

### `void onEncoder(void (*encoderHandler)(int32_t value))`

Registers an encoder event handler function. The handler function is called when changes are received and receives the current encoder value.

### `void onStepLeft (void (* stepLeftHandler) ())`

Registers a function that is an encoder event handler. Called for each left rotation step.

### `void onStepRight (void (* stepRightHandler) ())`

Registers a function that is an encoder event handler. Called for each step when rotated to the right.
