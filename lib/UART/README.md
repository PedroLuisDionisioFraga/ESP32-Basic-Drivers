# UART Driver

## Overview
This is a driver for the UART peripheral on the ESP32. It is a wrapper around the ESP-IDF UART driver.

## Modify the UART Configurations
Go to `drv_uart.c` and modify the `uart_config_t` structure to change the UART configurations.


## How It Works
First of all, initialize the UART driver by calling `uart_init` and passing the tx and rx pins as arguments. Then, you can use the `uart_write` to send data and `config_rx_task` passing the callback function to receive data.\
The `config_rx_task` was not already finish, your implementation is mocked, in `drv_uart.c` file has de TODO implementations to improve it.


## Interesting Points

### Handling Large Data Transmissions and Flow Control in UART Communication
In large data transmissions in UART communication, highlighting that UART frames can carry up to 9 bits, with the possibility of using the 9th bit for parity. For data larger than a frame, such as a 3000-character string, it's transmitted byte by byte. To avoid data loss from buffer overflow, flow control mechanisms like XON/XOFF (software-based) or RTS/CTS (hardware-based) are used to regulate transmission rates.

### UART RX interruption
It was deprecated in v5.0 of esp-idf, it used the `uart_isr_register()` function and created a task to handle the UART interrupt.

### A Pointer to a Pointer 
It is used to pass the address of a char pointer (char *ptr) to a function, allowing the function to modify the pointer itself, not just the data it points to, and can handle memory allocation.\
The caller must release the allocated memory later.
> In `_read_rx_buffer` function requires a pointer to a char pointer.

Dereferencing a `char **valid_data`:
1. Accessing the char pointer passed to `_read_rx_buffer` use `*`:
3. Acessing the value pointing by pointer passed to `_read_rx_buffer` use `**`



## Future Features
- Implement the Queue to handle the data received by the UART.
