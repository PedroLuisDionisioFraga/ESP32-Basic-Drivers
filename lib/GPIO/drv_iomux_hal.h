#ifndef DRV_IOMUX_HAL_H_
#define DRV_IOMUX_HAL_H_

#define IO_MUX_BASE 0x3FF49000

/**
 * @brief Register address for GPIO 21.
 *
 */
#define IO_MUX_GPIO21_REG (IO_MUX_BASE + 0x7C)

//* IO Mux Register Masks
#define MCU_SEL_MASK (7UL << (12UL))
#define FUN_DRV_MASK (3UL << (10UL))
#define FUN_IE_MASK (1UL << (9UL))
#define FUN_PULL_UP_MASK (1UL << (8UL))
#define FUN_PULL_DOWN_MASK (1UL << (7UL))
#define MCU_IE_MASK (1UL << (4UL))
#define MCU_PULL_UP_MASK (1UL << (3UL))
#define MCU_PULL_DOWN_MASK (1UL << (2UL))
#define SLP_SEL (1UL << (1UL))
#define MCU_OE (1UL << (0UL))

#endif // DRV_IOMUX_HAL_H_