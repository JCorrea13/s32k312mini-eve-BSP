/**
 * @file float_parser.h
 * @brief This file exposes utility functions to parse from string of characters to float.
 */
#if !defined(float_parser_)
#define float_parser_

typedef char (getNextCharacter)(void);

/**
 * Parses a string of characters to a float by getting characters until the 'delimiter' character is sent.
 * @param delimiter The character that determines the end of the string.
 * @getNextChar A function to get the next character.
 * @parsed_value a reference to the variable where the parsed value should be set.
 *
 * @return a char representing whether the parse was completed or failed.
 * @retval 1 if the parse was completed successfully.
 * @retval 0 if the parse failed.
 */
char parseFloat(char delimiter, getNextCharacter getNextChar, float *parsedValue);

#endif
