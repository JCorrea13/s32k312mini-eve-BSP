#include "integer_parser.h"
#include "../parse_utils.h"

char parseUint8_t(char delimiter, getNextCharacter getNextChar, uint8_t *parsedValue)
{
	*parsedValue = 0;
	char next = getNextChar();

	while(next != delimiter)
	{
		if(!isValidDigit(next))
		{
			*parsedValue = 0;
			return 0;
		}

		agregateIntegerToUint8_t(next, parsedValue);

		next = getNextChar();
	}

	return 1;
}
