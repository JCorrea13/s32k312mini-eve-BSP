/**
 * @file S32K312_UTILS.h
 * @brief Utility functions for the S32K312MINI-EVB.
 */

#if !defined(S32K312_UTILS_)
#define S32K312_UTILS_

#include "typedefs.h"
#include <stddef.h>

/**
 * This function simplifies writing to the SIUL2_MSCR_SSS registers for the GPIO module.
 */
uint32_t SIUL2_MSCR_SSS(uint8_t x);

#endif
