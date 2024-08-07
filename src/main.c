#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#include "drv_gpio.h"

#define LED_1 D27
#define LED_2 D26
#define LED_3 D25

#define BUTTON_1 D4

//#define MY_APP

esp_err_t configure_gpio_pull(uint32_t pin)
{
  gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL << pin), // Bit mask of the pin to configure
      .mode = GPIO_MODE_INPUT,       // Set the pin as input mode
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_ENABLE,
      .intr_type = GPIO_INTR_DISABLE // Disable interrupts for this pin

  };

  return gpio_config(&io_conf);
}

void app_main()
{
  // Outputs
  gpio_init(LED_1, GPIO_MODE_OUTPUT);
  gpio_init(LED_2, GPIO_MODE_OUTPUT);
  gpio_init(LED_3, GPIO_MODE_OUTPUT);

  // Inputs
#ifdef MY_APP
  gpio_init(BUTTON_1, GPIO_MODE_INPUT);
  gpio_en_pulldown(BUTTON_1);
#else
  configure_gpio_pull(BUTTON_1);
#endif

  gpio_state_t state /* = GPIO_STATE_HIGH*/;
  while (true)
  {
    // gpio_write(LED_1, state);
    // vTaskDelay(2500 / portTICK_PERIOD_MS);

    // gpio_read(LED_1, &state);
    // gpio_write(LED_2, state);
    // vTaskDelay(2500 / portTICK_PERIOD_MS);

    // gpio_read(LED_2, &state);
    // gpio_write(LED_3, state);

    gpio_read(BUTTON_1, &state);
    ESP_LOGI("GPIO", "Button 1: %d", (uint8_t)state);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // break;
  }
}