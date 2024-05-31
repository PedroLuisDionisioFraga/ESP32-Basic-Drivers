/**
 * @file interrupt.h
 * @brief Functions for configuring GPIO interrupts.
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "drv_gpio.h"

/**
 * @brief Configure a GPIO pin for interrupts.
 *
 * This function configures a GPIO pin as an input and sets up an interrupt handler for it.
 *
 * @param[in] intr_type The type of interrupt to configure. This should be one of the `gpio_int_type_t` values.
 * @param[in] pinout The number of the GPIO pin to configure.
 *
 * @return `ESP_OK` if the configuration was successful, or an error code if there was a problem.
 */
esp_err_t config_interruption(gpio_pinout_t pinout, gpio_int_type_t intr_type, void gpio_isr_handler(void *arg));

esp_err_t exclude_interruption(gpio_pinout_t pinout);

#endif // INTERRUPT_H_