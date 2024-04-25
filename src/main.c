#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#include "gpio.h"

#define LED_PIN BUILTIN_LED

void app_main()
{
  gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
  gpio_set_level(LED_PIN, GPIO_STATE_LOW);

  while (true)
  {
    gpio_set_level(LED_PIN, GPIO_STATE_HIGH);
    esp_delay(1000);
    gpio_set_level(LED_PIN, GPIO_STATE_LOW);
    esp_delay(1000);
  }
}