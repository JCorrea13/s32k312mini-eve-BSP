/**
 * @file parser_utils.h
 * @brief This file exposes utility functions to parse for parsing.
 */

#if !defined(parse_utils_)
#define parse_utils_

#include <stdint.h>

static inline void agregateIntegerToUint8_t(char value, uint8_t *parsedValue)
{
	char intValue = (int)value - 48;
	*parsedValue = (*parsedValue * 10) + intValue;
}

static inline char isValidDigit(char value)
{
	return value >= '0' && value <= '9';
}

#endif
