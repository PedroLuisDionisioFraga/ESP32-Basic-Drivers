/**
 * @file gpio.h
 * @brief Header file for GPIO pinout definitions and utility functions.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <driver/gpio.h>
#include <hal/gpio_types.h>
#include <esp_err.h>

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

#endif // GPIO_H_
