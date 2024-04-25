# GPIO Header File Documentation

This header file, `gpio.h`, contains definitions and enumerators for the GPIO (General Purpose Input Output) pins on the ESP32 microcontrolador.

## GPIO Pinout Definitions

The `gpio_pinout_t` enumeration defines the GPIO pins on the ESP32. Each pin is associated with a specific function:

- **General Pins:** These are general purpose pins that can be used for various functions. They are labeled as `D<number>`, for example `D13`, `D12`, etc.
- **LED:** The `INTERNAL_LED` pin is used to control the built-in LED on the ESP32.
- **UART:** The `RX_0`, `TX_0`, `RX_2`, and `TX_2` pins are used for UART communication.
- **I2C:** The `SDA` and `SCL` pins are used for I2C (Inter-Integrated Circuit) communication.
- **SPI:** The `MISO`, `MOSI`, `SCK`, and `CS` pins are used for SPI communication. There are also separate definitions for VSPI and HSPI.
- **ADC:** The `ADC1_<number>` and `ADC2_<number>` pins are used for analog-to-digital conversion.
- **DAC:** The `DAC1` and `DAC2` pins are used for digital-to-analog conversion.
- **Touch:** The `TOUCH<number>` pins are used for capacitive touch sensors.
- **RTC:** The `RTC_GPIO<number>` pins are used for the Real Time Clock.
- **Strapping:** The `STRAP<number>` pins are used for strapping pins.
- **Disable GPIO:** The `DISABLE` pin is used to disable a GPIO.

## GPIO State Definitions

The `gpio_state_t` enumeration defines the possible states of a GPIO pin:

- `GPIO_STATE_LOW`: The pin is in a low state (0V).
- `GPIO_STATE_HIGH`: The pin is in a high state (3.3V).

## Example

Then, you can use the defined pin names and states in your code. For example, to set a pin to HIGH:
```c
#include "gpio.h"

gpio_set_level(D13, GPIO_STATE_HIGH);
```