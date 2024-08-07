/**
 * @file drv_gpio.c
 * @author Pedro Luis Dionísio Fraga (pedrodfraga@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2024-07-12
 *
 * @copyright Copyright (c) 2024
 */

#include <stdbool.h>
#include <soc/gpio_reg.h>

#include "drv_gpio.h"
#include "io_mux_pins.h"

#define GET_GPIO_PIN_REG(pin) (GPIO_PIN0_REG + ((pin) * 0x04))
#define PULL_DOWN_M (1UL << 7)
#define PULL_UP_M (1UL << 8)
#define MCU_SEL_GPIO_M (2UL << 12)  // Reference in `io_mux_reg.h`

return_code_t gpio_init(uint32_t pin, gpio_mode_t mode)
{
  if (mode == GPIO_MODE_OUTPUT)
    *((volatile uint32_t *)GPIO_ENABLE_W1TS_REG) |= (1UL << pin);
  else if (mode == GPIO_MODE_INPUT)
    *((volatile uint32_t *)GPIO_ENABLE_W1TC_REG) |= (1UL << pin);
  else
    return GPIO_ERR_INVALID_MODE;

  // TODO: Add MCU_SEL_M to select the GPIO function
  *((volatile uint32_t *)io_mux_pins[pin]) |= MCU_SEL_M;

  return OK;
}

return_code_t gpio_write(uint32_t pin, gpio_state_t state)
{
  if (state == GPIO_STATE_HIGH)
    *((volatile uint32_t *)GPIO_OUT_W1TS_REG) |= (1UL << pin);
  else if (state == GPIO_STATE_LOW)
    *((volatile uint32_t *)GPIO_OUT_W1TC_REG) |= (1UL << pin);
  else
    return GPIO_ERR_INVALID_MODE;

  return OK;
}

bool _is_gpio_output(uint32_t pin)
{
  return *((volatile uint32_t *)GPIO_OUT_REG) & (1UL << pin);
}

return_code_t gpio_read(uint32_t pin, gpio_state_t *state)
{
  uint32_t value;
  bool is_output = _is_gpio_output(pin);
  if (is_output)
    value = *((volatile uint32_t *)GPIO_OUT_REG);
  else
    value = *((volatile uint32_t *)GPIO_IN_REG);

  *state = (value & (1UL << pin)) ? GPIO_STATE_HIGH : GPIO_STATE_LOW;

  return OK;
}

return_code_t gpio_en_pullup(uint32_t pin)
{
  *((volatile uint32_t *)io_mux_pins[pin]) |= PULL_UP_M;
  *((volatile uint32_t *)io_mux_pins[pin]) &= ~PULL_DOWN_M;
  return OK;
}

return_code_t gpio_en_pulldown(uint32_t pin)
{
  *((volatile uint32_t *)io_mux_pins[pin]) |= PULL_DOWN_M;
  *((volatile uint32_t *)io_mux_pins[pin]) &= ~PULL_UP_M;
  return OK;
}
