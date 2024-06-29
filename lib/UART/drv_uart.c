/**
 * @file drv_uart.c
 * @author Pedro Luis Dionísio Fraga (pedrodfraga@hotmail.com)
 * @brief UART driver implementation
 *
 * If you need change the UART configuration, you can modify the `uart_config` in the `init_uart()` function.
 * @version 0.1
 * @date 2024-05-31
 *
 * @section license License
 * @copyright (c) 2024 Pedro Luis Dionísio Fraga
 *
 */

#include <stdlib.h>
#include <string.h>
#include <driver/uart.h>
#include <freertos/FreeRTOS.h>

#include "drv_uart.h"

#define DEBUG_MODE 0

static char *tx_buffer = NULL;
static char *rx_buffer = NULL;

static uart_port_t uart_num;

return_code_t uart_init(const gpio_pinout_t tx_pin, const gpio_pinout_t rx_pin)
{
  tx_buffer = (char *)malloc(BUF_SIZE);
  if (tx_buffer == NULL)
    return UART_ERR_MALLOC;

  rx_buffer = (char *)malloc(BUF_SIZE);
  if (rx_buffer == NULL)
    return UART_ERR_MALLOC;

  // Validate UART pins
  if (tx_pin == TX_0 && rx_pin == RX_0)
    uart_num = UART_NUM_0;
  else if (tx_pin == TX_2 && rx_pin == RX_2)
    uart_num = UART_NUM_2;
  else
    return UART_ERR_INVALID_PORTS;

#if DEBUG_MODE
  ESP_LOGI("UART", "Using UART0%d\n", uart_num);
#endif

  //* Modify it if necessary
  const uart_config_t uart_config = {
      .baud_rate = 115200,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};

  esp_err_t ret;

  ret = uart_param_config(uart_num, &uart_config);
  if (ret != ESP_OK)
    return UART_ERR_CONFIG_PARAMS;

  ret = uart_set_pin(uart_num, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  if (ret != ESP_OK)
    return UART_ERR_CONFIG_PARAMS;

  // TODO: Try it using #if or #ifndef
  if (uart_is_driver_installed(uart_num))
    return OK;

  // TODO: Remove magic numbers
  ret = uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, 0);
  if (ret != ESP_OK)
    return UART_ERR_CONFIG_PARAMS;

#if DEBUG_MODE
  ESP_LOGI("UART", "UART0%d Configured with Success\n", uart_num);
#endif

  return OK;
}

return_code_t uart_write(const char *data)
{
  if (data == NULL)
    return UART_ERR_CONFIG_PARAMS;

  if (uart_num == UART_NUM_0)
    return UART_ERR_CONFIG_PARAMS;

  int ret;
  ret = uart_write_bytes(uart_num, data, strlen(data));
  if (ret < 0)
    return UART_ERR_SEND_DATA;

#if DEBUG_MODE
  ESP_LOGI("UART", "Data size: %d bytes\n", ret);
  ESP_LOGI("UART", "Data sent: %s\n", data);
#endif

  return OK;
}

return_code_t _read_rx_buffer(char **valid_data)
{
  uint8_t buffer_length = uart_read_bytes(uart_num, rx_buffer, 2 * BUF_SIZE, 100 / portTICK_PERIOD_MS);
  if (buffer_length < 1)
    return UART_EMPTY_RX_BUFFER;

#if DEBUG_MODE
  ESP_LOGI("UART", "Data size: %d bytes\n", buffer_length);
  ESP_LOG_BUFFER_CHAR("UART RX Buffer", rx_buffer, buffer_length);
#endif

  *valid_data = (char *)malloc(buffer_length);
  if (*valid_data == NULL)
    return UART_ERR_MALLOC;

  memcpy(*valid_data, rx_buffer, buffer_length);
  (*valid_data)[buffer_length] = '\0';

#if DEBUG_MODE
  ESP_LOGI("UART", "Data received: %s\n", *valid_data);
#endif

  return OK;
}

esp_err_t clean_rx_buffer()
{
  return uart_flush(uart_num);
}

return_code_t delete_uart_driver()
{
  esp_err_t ret;
  ret = uart_driver_delete(uart_num);
  if (ret != ESP_OK)
    return UART_ERR_CONFIG_PARAMS;

  return OK;
}

return_code_t config_rx_task(void *pvParameters)
{
  BaseType_t xReturned;
  // TODO: Improve this task creation
  xReturned = xTaskCreate(_rx_event_task, "uart_rx_task", BUF_SIZE * 2, NULL, 10, NULL);

  return xReturned == pdPASS ? OK : UART_ERR_CONFIG_PARAMS;
}

void _rx_event_task(void *pvParameters)
{
  // TODO: Verify if this loop is necessary in task context
  while (1)
  {
    char *rx_data = NULL;
    return_code_t ret;
    ret = _read_rx_buffer(&rx_data);
    if (ret != OK)
      continue;

    // TODO: Put the function `pvParameters` here and find a way to shared the rx_data to it
    ESP_LOGI("UART", "Data received: %s", rx_data == NULL ? "NULL" : rx_data);

    free(rx_data);
  }

  free(rx_buffer);
}
