#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#include "drv_gpio.h"
#include "drv_uart.h"

#define LED_PIN BUILTIN_LED

void app_main()
{
  (void)init_uart(TX_2, RX_2);
  (void)config_rx_task(NULL);  // TODO: Works it

  while (1)
  {
    (void)send_data("Hello World!\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}