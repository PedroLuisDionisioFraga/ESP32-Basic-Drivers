#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#include "drv_gpio.h"
#include "Externals/external_interrupt.h"

#define LED_RED GPIO_NUM_26
#define LED_YELLOW GPIO_NUM_27

#define BUTTON_TO_RED_LED GPIO_NUM_22
#define BUTTON_TO_YELLOW_LED GPIO_NUM_23

static int state = 0;

int count = 0;

void toggle_led(void *arg)
{
  gpio_num_t pinout = (gpio_num_t)arg;
  count++;
  state = !state;

  if (pinout == BUTTON_TO_YELLOW_LED)
    pinout = LED_YELLOW;

  gpio_set_level(pinout, state);

  if(count == 2)
    exclude_interruption(BUTTON_TO_YELLOW_LED);
}

void configure_leds()
{
  gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
  gpio_set_level(LED_RED, 0);

  gpio_set_direction(LED_YELLOW, GPIO_MODE_OUTPUT);
  gpio_set_level(LED_YELLOW, 0);
}

void configure_interrupts()
{
  esp_err_t ret;
  //! Only the first interruption is working
  ret = config_interruption(BUTTON_TO_YELLOW_LED, GPIO_INTR_NEGEDGE, &toggle_led);
  if (ret != ESP_OK)
    ESP_LOGI("INTERRUPT", "Error configuring interruption 1.");
}

void app_main()
{
  configure_leds();

  configure_interrupts();

  while (true)
  {
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    ESP_LOGI("LED_YELLOW", "State: %d, Count: %d", state, count);
  }
}
