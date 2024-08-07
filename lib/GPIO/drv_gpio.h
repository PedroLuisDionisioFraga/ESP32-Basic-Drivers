/**
 * @file gpio.h
 * @brief Header file for GPIO pinout definitions and utility functions.
 *
 * @note It depend of the `return_code.h` and `gpio_types.h` files.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <driver/gpio.h>
#include <hal/gpio_types.h>

#include "return_code.h"

/**
 * @brief Enumeration of GPIO pinout definitions.
 */
typedef enum
{
  // Pins Up
  D13 = GPIO_NUM_13,
  D12 = GPIO_NUM_12,
  D14 = GPIO_NUM_14,
  D27 = GPIO_NUM_27,
  D26 = GPIO_NUM_26,
  D25 = GPIO_NUM_25,
  D33 = GPIO_NUM_33,
  D32 = GPIO_NUM_32,
  D35 = GPIO_NUM_35,
  D34 = GPIO_NUM_34,
  // Pins Down
  D15 = GPIO_NUM_15,
  D4 = GPIO_NUM_4,
  D5 = GPIO_NUM_5,
  D18 = GPIO_NUM_18,
  D19 = GPIO_NUM_19,
  D21 = GPIO_NUM_21,
  D22 = GPIO_NUM_22,
  D23 = GPIO_NUM_23,

  // LED
  BUILTIN_LED = GPIO_NUM_2,

  // UART
  RX_0 = GPIO_NUM_3,
  TX_0 = GPIO_NUM_1,
  RX_2 = GPIO_NUM_16,
  TX_2 = GPIO_NUM_17,

  // I2C
  SDA = GPIO_NUM_21,
  SCL = GPIO_NUM_22,

  // VSPI
  MISO_V = GPIO_NUM_19,
  MOSI_V = GPIO_NUM_23,
  CLK_V = GPIO_NUM_18,
  CS_V = GPIO_NUM_5,

  // HSPI
  MISO_H = GPIO_NUM_12,
  MOSI_H = GPIO_NUM_13,
  CLK_H = GPIO_NUM_14,
  CS_H = GPIO_NUM_15,

  // SPI
  MOSI = GPIO_NUM_23,
  MISO = GPIO_NUM_19,
  SCK = GPIO_NUM_18,
  CS = GPIO_NUM_5,

  // ADC
  ADC1_0 = GPIO_NUM_36,
  ADC1_3 = GPIO_NUM_39,
  ADC1_4 = GPIO_NUM_32,
  ADC1_5 = GPIO_NUM_33,
  ADC1_6 = GPIO_NUM_34,
  ADC1_7 = GPIO_NUM_35,
  ADC2_0 = GPIO_NUM_4,
  ADC2_2 = GPIO_NUM_2,
  ADC2_3 = GPIO_NUM_15,
  ADC2_4 = GPIO_NUM_13,
  ADC2_5 = GPIO_NUM_12,
  ADC2_6 = GPIO_NUM_14,
  ADC2_7 = GPIO_NUM_27,
  ADC2_8 = GPIO_NUM_25,
  ADC2_9 = GPIO_NUM_26,

  // DAC
  DAC1 = GPIO_NUM_25,
  DAC2 = GPIO_NUM_26,

  // Touch
  TOUCH0 = GPIO_NUM_4,
  TOUCH2 = GPIO_NUM_2,
  TOUCH3 = GPIO_NUM_15,
  TOUCH4 = GPIO_NUM_13,
  TOUCH5 = GPIO_NUM_12,
  TOUCH6 = GPIO_NUM_14,
  TOUCH7 = GPIO_NUM_27,
  TOUCH8 = GPIO_NUM_33,
  TOUCH9 = GPIO_NUM_32,

  // RTC
  RTC_GPIO00 = GPIO_NUM_36,
  RTC_GPIO03 = GPIO_NUM_39,
  RTC_GPIO04 = GPIO_NUM_34,
  RTC_GPIO05 = GPIO_NUM_35,
  RTC_GPIO06 = GPIO_NUM_25,
  RTC_GPIO07 = GPIO_NUM_26,
  RTC_GPIO08 = GPIO_NUM_33,
  RTC_GPIO09 = GPIO_NUM_32,
  RTC_GPIO10 = GPIO_NUM_4,
  RTC_GPIO12 = GPIO_NUM_2,
  RTC_GPIO13 = GPIO_NUM_15,
  RTC_GPIO14 = GPIO_NUM_13,
  RTC_GPIO15 = GPIO_NUM_12,
  RTC_GPIO16 = GPIO_NUM_14,
  RTC_GPIO17 = GPIO_NUM_27,

  // Strapping
  STRAP1 = GPIO_NUM_12,
  STRAP2 = GPIO_NUM_5,
  STRAP3 = GPIO_NUM_2,
  STRAP4 = GPIO_NUM_15,

  // Disable GPIO
  DISABLE = GPIO_NUM_NC,
} gpio_pinout_t;

/**
 * @brief Enumeration of GPIO pinout definitions.
 */
typedef enum
{
  GPIO_STATE_LOW = 0,
  GPIO_STATE_HIGH = 1,
} gpio_state_t;

/**
 * @brief Initializes a GPIO pin with the specified mode.
 *
 * @param pin The GPIO pin number.
 * @param mode The desired mode of the GPIO pin (input or output).
 * @return A return code indicating success or failure (OK or GPIO_ERR_INVALID_MODE).
 *
 * This function uses the following registers to set the pin mode:
 * - `GPIO_ENABLE_W1TS_REG`: Write 1 to set the output enable state for GPIO pins 0-31.
 * - `GPIO_ENABLE_W1TC_REG`: Write 1 to clear the output enable state for GPIO pins 0-31.
 *
 * @note Differences between GPIO enable registers:
 * - `GPIO_ENABLE_REG`: Main read/write register for enabling/disabling GPIO output.
 * - `GPIO_ENABLE_W1TS_REG`: Write-only, sets specific GPIO bits without affecting others.
 * - `GPIO_ENABLE_W1TC_REG`: Write-only, clears specific GPIO bits without affecting others.
 */
return_code_t gpio_init(uint32_t pin, gpio_mode_t mode);

/**
 * @brief Set the GPIO pin to the specified state.
 *
 * This function sets the specified GPIO pin to either a high or low state.
 *
 * @param pin The GPIO pin number to be set.
 * @param state The state to set the GPIO pin to.
 *
 * @note The cast on GPIO_OUT_W1TS_REG address to a volatile uint32_t pointer and dereference it to write the value. This ensures direct and immediate access to the hardware register.
 */
return_code_t gpio_write(uint32_t pin, gpio_state_t state);

/**
 * @brief Read the state of a GPIO pin.
 *
 * This function reads the current state of the specified GPIO pin (high or low).
 *
 * @param pin The GPIO pin number.
 * @param state A pointer to store the read state of the GPIO pin (high or low).
 * @return A return code indicating success (OK).
 *
 * @note The `GPIO_IN_REG` register contains the input values of GPIO pins 0-31.
 */
return_code_t gpio_read(uint32_t pin, gpio_state_t *state);

/**
 * @brief Enables the internal pull-up resistor for a GPIO pin.
 *
 * This function configures a specified GPIO pin to enable its internal pull-up resistor.
 * It directly manipulates the IO MUX register corresponding to the pin to set the pull-up control bit and clear the pull-down control bit.
 *
 * @param pin The GPIO pin number for which to enable the pull-up resistor.
 *
 * @note The available pins for pull-up are 14, 16(RX_2), 17(TX_2), 18, 19, 21, 22 and 23
 *
 * @return return_code_t Returns OK if the operation was successful.
 */
return_code_t gpio_en_pullup(uint32_t pin);

/**
 * @brief Enables the internal pull-down resistor for a GPIO pin.
 *
 * This function configures a specified GPIO pin to enable its internal pull-down resistor.
 * It directly manipulates the IO MUX register corresponding to the pin to set the pull-down control bit and clear the pull-up control bit.
 *
 * @param pin The GPIO pin number for which to enable the pull-down resistor.
 *
 * @note The available pins for pull-up are 14, 16(RX_2), 17(TX_2), 18, 19, 21, 22 and 23
 *
 * @return return_code_t Returns OK if the operation was successful.
 */
return_code_t gpio_en_pulldown(uint32_t pin);

#endif // GPIO_H_
