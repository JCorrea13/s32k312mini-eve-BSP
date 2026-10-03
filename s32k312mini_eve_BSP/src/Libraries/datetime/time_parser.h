/**
 * @file time_parser.h
 * @brief This file exposes utility functions to parse from string of characters to a time struct.
 */
#if !defined(time_parser_)
#define time_parser_

#include <stdint.h>

typedef char (getNextCharacter)(void);

typedef struct
{
	uint8_t hour;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t milliseconds;
} time_t;

/**
 * Parses a string of characters to a time_t struct by getting characters until the 'delimiter' character is sent.
 * @param delimiter The character that determines the end of the string.
 * @getNextChar A function to get the next character.
 * @parsed_value a reference to the variable where the parsed value should be set.
 *
 * @return a char representing whether the parse was completed or failed.
 * @retval 1 if the parse was completed successfully.
 * @retval 0 if the parse failed.
 */
char parseTime(char delimiter, getNextCharacter getNextChar, time_t *parsedValue);

#endif
