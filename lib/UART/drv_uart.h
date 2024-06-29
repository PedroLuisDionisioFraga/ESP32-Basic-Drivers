/**
 * @file drv_uart.h
 * @author Pedro Luis Dionísio Fraga (pedrodfraga@hotmail.com)
 * @brief UART driver
 * @version 0.1
 * @date 2024-05-31
 *
 * @section license License
 * @copyright (c) 2024 Pedro Luis Dionísio Fraga *
 */

#ifndef DRV_UART_H_
#define DRV_UART_H_

#include <freertos/queue.h>
#include <stdlib.h>
#include <esp_log.h>

#include "drv_gpio.h"
#include "return_code.h"

#define BAUD_RATE 115200
#define DATA_BITS UART_DATA_8_BITS
#define STOP_BITS UART_STOP_BITS_1
#define PARITY UART_PARITY_DISABLE
#define FLOW_CTRL UART_HW_FLOWCTRL_DISABLE
#define BUF_SIZE 1024

/**
 * @brief Initializes the UART with specified TX and RX pins.
 *
 * This function initializes the UART peripheral with the specified TX and RX GPIO pins. It allocates buffers for TX and RX, configures UART settings such as baud rate, data bits, parity, stop bits, and flow control. It also sets the UART pins and installs the UART driver if not already installed.
 *
 * @param tx_pin The GPIO pin number used for UART transmission.
 * @param rx_pin The GPIO pin number used for UART reception.
 *
 * @return return_code_t Returns OK on success or an error code on failure. Possible error codes include UART_ERR_MALLOC for memory allocation failures, UART_ERR_INVALID_PORTS for invalid TX/RX pin combinations, and UART_ERR_CONFIG_PARAMS for failures in configuring UART parameters or installing the UART driver.
 *
 * @note This function uses a predefined buffer size (BUF_SIZE) for both TX and RX buffers. It also assumes UART_NUM_0 or UART_NUM_2 based on the pin numbers provided.
 *
 * @warning The function uses magic numbers for buffer sizes during UART driver installation. Consider defining these numbers with meaningful constants.
 *
 * @todo Replace magic numbers with defined constants for buffer sizes.
 * @todo Consider using conditional compilation to handle debug mode logging more elegantly.
 */
return_code_t uart_init(gpio_pinout_t tx_pin, gpio_pinout_t rx_pin);

/**
 * @brief Sends a string of data over UART.
 *
 * This function sends a string of data through the UART interface specified by the global variable `uart_num`. It checks if the input data pointer is not NULL, calculates the length of the data using `strlen`, and then sends the data using `uart_write_bytes`. If the data is successfully sent, it returns OK. Otherwise, it returns an error code.
 *
 * @param data Pointer to the string of data to be sent. Must not be NULL.
 *
 * @return return_code_t Returns OK if the data was successfully sent. Returns UART_ERR_CONFIG_PARAMS if the input data pointer is NULL. Returns UART_ERR_SEND_DATA if there was an error during the transmission.
 *
 * @note This function relies on the global variable `uart_num` to specify the UART port. Ensure `uart_num` is initialized before calling this function.
 *
 * @warning The function assumes `uart_num` has been correctly initialized with a valid UART port number.
 *
 */
return_code_t uart_write(const char *data);

/**
 * @brief Reads data from the UART RX buffer.
 *
 * This function reads data from the UART RX buffer and returns it through the `valid_data` pointer. It checks if the `valid_data` pointer is not NULL and then reads the data from the RX buffer. If data is successfully read, it returns OK. Otherwise, it returns an error code.
 *
 * @param valid_data Pointer to the location where the read data will be stored. Must not be NULL.
 *
 * @return return_code_t Returns OK if data was successfully read from the RX buffer. Returns UART_ERR_CONFIG_PARAMS if the input data pointer is NULL. Returns UART_ERR_READ_DATA if there was an error during data reading.
 *
 * @note This function uses the global variable `rx_buffer` to store the received data. Ensure `rx_buffer` is correctly initialized before calling this function.
 *
 * @warning The function assumes `rx_buffer` has been correctly initialized with a valid buffer size.
 */
return_code_t _read_rx_buffer(char **valid_data);

/**
 * @brief Configures the UART RX task.
 *
 * This function creates a FreeRTOS task that listens for incoming data on the UART RX buffer. It uses the `_rx_event_task` function as the task function and passes the `data` pointer as the task parameter. If the task is successfully created, it returns OK. Otherwise, it returns an error code.
 *
 * @param pvParameters Pointer to the task parameters. Not used in this function.
 *
 * @return return_code_t Returns OK if the task was successfully created. Returns UART_ERR_CONFIG_PARAMS if there was an error during task creation.
 *
 * @note The `data` pointer is a global variable and is already allocated in the `init_uart()` function. Ensure `init_uart()` is called before configuring the RX task.
 */
return_code_t config_rx_task(void *pvParameters);

/**
 * @brief Task for handling UART RX events.
 *
 * This task continuously monitors the UART RX buffer for incoming data. When data is received, it reads the data from the RX buffer, logs the received data, and then frees the allocated memory for the received data. The task runs in an infinite loop, making it suitable for real-time data handling in embedded systems.
 *
 * @param pvParameters User-defined parameters passed to the task. Currently unused in the function body.
 *
 * @note This function is designed to be run as a FreeRTOS task. It assumes that `_read_rx_buffer` is a function that reads data from the UART RX buffer and allocates memory for the received data, which must be freed after use.
 *
 * @warning The function contains a TODO comment regarding the necessity of the loop in the task context and another regarding the use of `pvParameters` for sharing received data. These aspects need to be addressed to ensure the function's completeness and efficiency.
 *
 * @todo Verify the necessity of the continuous loop within the task context.
 * @todo Implement a mechanism to use `pvParameters` for sharing `rx_data` with other parts of the system.
 */
void _rx_event_task(void *pvParameters);

#endif // DRV_UART_H_
