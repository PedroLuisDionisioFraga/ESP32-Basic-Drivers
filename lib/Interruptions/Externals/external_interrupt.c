#include <esp_intr_alloc.h>

#include "external_interrupt.h"

#define GPIO_ISR_SERVICE_DEFAULT_FLAGS 0

esp_err_t config_interruption(gpio_pinout_t pinout, gpio_int_type_t intr_type, void gpio_isr_handler(void *arg))
{
  esp_err_t ret;
  gpio_config_t io_conf;

  io_conf.pin_bit_mask = 1ULL << pinout;
  io_conf.intr_type = intr_type;
  io_conf.mode = GPIO_MODE_INPUT;

  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;

  ret = gpio_config(&io_conf);
  if (ret != ESP_OK)
    return ret;

  ret = gpio_set_intr_type(pinout, intr_type);
  if (ret != ESP_OK)
    return ret;

  ret = gpio_install_isr_service(GPIO_ISR_SERVICE_DEFAULT_FLAGS);
  if (ret != ESP_OK)
    return ret;

  gpio_isr_handler_add(pinout, gpio_isr_handler, (void *)pinout);

  return ESP_OK;
}

esp_err_t exclude_interruption(gpio_pinout_t pinout)
{
  esp_err_t ret;
  ret = gpio_isr_handler_remove(pinout);

  return ret;
}
