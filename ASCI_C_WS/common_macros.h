/******************************************************************************
 *
 * Module: Common Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Header file for commonly used macros
 *
 * Author: Muhammad Salah
 *
 *******************************************************************************/

#ifndef COMMON_MACROS /* Guard */
#define COMMON_MACROS

/* Set a specific bit in a register */
#define SET_BIT(REG, BIT) (REG |= (1 << BIT))

/* Clear a specific bit in a register */
#define CLEAR_BIT(REG, BIT) (REG &= ~(1 << BIT))

/* Toggle a specific bit in a register */
#define TOGGLE_BIT(REG, BIT) (REG ^= (1 << BIT))

/* Rotate bits in a register to the right */
#define ROR(REG, num) (REG = (REG >> num) | (REG << (8 - num)))

/* Rotate bits in a register to the left */
#define ROL(REG, num) (REG = (REG << num) | (REG >> (8 - num)))

/* Check if a specific bit in a register is set */
#define BIT_IS_SET(REG, BIT) (REG & (1 << BIT))

/* Check if a specific bit in a register is clear */
#define BIT_IS_CLEAR(REG, BIT) (!(REG & (1 << BIT)))

/* Get the value of a specific bit in a register */
#define GET_BIT(REG, BIT) ((REG >> BIT) & 1)

#endif
