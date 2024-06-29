/**
 * @file return_code.h
 * @author Pedro Luis Dionísio Fraga (pedrodfraga@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2024-05-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef RETURN_CODE_H_
#define RETURN_CODE_H_

typedef enum
{
  //* OK
  OK = 0x0000,

  //* UART
  UART_ERR_INVALID_PORTS,
  UART_ERR_CONFIG_PARAMS,
  UART_ERR_READ_DATA,
  UART_ERR_SEND_DATA,
  UART_ERR_MALLOC,
  UART_EMPTY_RX_BUFFER,

} return_code_t;

#endif // RETURN_CODE_H_