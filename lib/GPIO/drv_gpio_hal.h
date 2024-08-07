/**
 * @file drv_gpio_hal.h
 * @author Pedro Luis Dionísio Fraga (pedrodfraga@hotmail.com)
 * @brief GPIO HAL definitions for the ESP32 microcontrolador.
 * @version 0.1
 * @date 2024-07-12
 *
 * @note Aligning registers to certain boundaries (like 4-byte boundaries) can improve access efficiency. Many CPUs are optimized to access data aligned to their word size, which is often 4 bytes (32 bits) for many microcontrollers. This alignment can speed up data access and reduce the number of bus cycles needed for register access.
 *
 * @copyright Copyright (c) 2024
 */


#ifndef DRV_GPIO_HAL_H_
#define DRV_GPIO_HAL_H_

/**
 * @file drv_gpio_hal.h
 * @brief This file contains the definitions of GPIO registers and constants for the ESP32 microcontroller.
 */

/**
 * @def GPIO_BASE
 * @brief Base address of the GPIO peripheral.
 */
#define GPIO_BASE 0x3FF44000

/**
 * @def GPIO_OUT_REG
 * @brief Address of the GPIO output register.
 *
 * @note Write and read access.
 */
#define GPIO_OUT_REG (GPIO_BASE + 0x04)

/**
 * @def GPIO_OUT_W1TS_REG
 * @brief Address of the GPIO output register for writing 1 to set (W1TS).
 *
 * @note Write access.
 */
#define GPIO_OUT_W1TS_REG (GPIO_BASE + 0x08)

/**
 * @def GPIO_OUT_W1TC_REG
 * @brief Address of the GPIO output register for writing 1 to clear (W1TC).
 *
 * @note Write access.
 */
#define GPIO_OUT_W1TC_REG (GPIO_BASE + 0x0C)

/**
 * @def GPIO_ENABLE_REG
 * @brief Address of the GPIO enable register.
 *
 * @note Write and read access.
 */
#define GPIO_ENABLE_REG (GPIO_BASE + 0x20)

/**
 * @def GPIO_ENABLE_W1TS_REG
 * @brief Address of the GPIO enable register for writing 1 to set (W1TS).
 *
 * @note Write access.
 */
#define GPIO_ENABLE_W1TS_REG (GPIO_BASE + 0x24)

/**
 * @def GPIO_ENABLE_W1TC_REG
 * @brief Address of the GPIO enable register for writing 1 to clear (W1TC).
 *
 * @note Write access.
 */
#define GPIO_ENABLE_W1TC_REG (GPIO_BASE + 0x28)

/**
 * @def GPIO_IN_REG
 * @brief Address of the GPIO input register.
 *
 * @note Read access.
 */
#define GPIO_IN_REG (GPIO_BASE + 0x3C)

/**
 * @def GPIO_IN_SELECT_REG
 * @brief Address of the GPIO input select register.
 *
 * @note Write access.
 */
#define GPIO_IN_SELECT_REG (DR_REG_GPIO_BASE + 0x0130)

/**
 * @def GPIO_SIG0_IN_SEL
 * @brief Send the input signal the GPIO matrix.
 *
 * @note Write access.
 */
#define GPIO_SIG0_IN_SEL  (1UL << 7)

/**
 * @def ALL_PINS
 * @brief Constant representing all GPIO pins.
 */
#define ALL_PINS 0xFFFFFFFF



#endif /* DRV_GPIO_HAL_H_ */

