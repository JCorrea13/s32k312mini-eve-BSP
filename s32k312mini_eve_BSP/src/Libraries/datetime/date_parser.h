/**
 * @file date_parser.h
 * @brief This file exposes utility functions to parse from string of characters to a date struct.
 */
#if !defined(date_parser_)
#define date_parser_

#include <stdint.h>

typedef char (getNextCharacter)(void);

typedef struct
{
	uint8_t day;
	uint8_t month;
	uint8_t year;
} date_t;

/**
 * Parses a string of characters with the format DDMMYY to a date_t struct by getting characters until the 'delimiter' character is sent.
 * @param delimiter The character that determines the end of the string.
 * @getNextChar A function to get the next character.
 * @parsed_value a reference to the variable where the parsed value should be set.
 *
 * @return a char representing whether the parse was completed or failed.
 * @retval 1 if the parse was completed successfully.
 * @retval 0 if the parse failed.
 */
char parseDate(char delimiter, getNextCharacter getNextChar, date_t *parsedValue);

#endif
