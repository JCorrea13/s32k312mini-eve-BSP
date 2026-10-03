/**
 * @file integer_parser.h
 * @brief This file exposes utility functions to parse from string of characters to integer types.
 */
#if !defined(integer_parser_)
#define integer_parser_

#include <stdint.h>

typedef char (getNextCharacter)(void);

/**
 * Parses a string of characters to a uint8_t by getting characters until the 'delimiter' character is sent.
 * @param delimiter The character that determines the end of the string.
 * @getNextChar A function to get the next character.
 * @parsed_value a reference to the variable where the parsed value should be set.
 *
 * @return a char representing whether the parse was completed or failed.
 * @retval 1 if the parse was completed successfully.
 * @retval 0 if the parse failed.
 */
char parseUint8_t(char delimiter, getNextCharacter getNextChar, uint8_t *parsedValue);

#endif
