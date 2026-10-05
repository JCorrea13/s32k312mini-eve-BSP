#include "float_parser.h"
#include "../parse_utils.h"

static inline void agregateInteger(char value, float *parsedValue)
{
	char intValue = (int)value - 48;
	*parsedValue = (*parsedValue * 10) + intValue;
}

static inline void agregateFraction(char value, float *parsedValue, float multiplier)
{
	char intValue = (int)value - 48;
	*parsedValue = (*parsedValue) + (intValue * multiplier);
}

char parseFloat(char delimiter, getNextCharacter getNextChar, float *parsedValue)
{
	*parsedValue = 0;
	char next = getNextChar();

	char inFraction = 0;
	float fractionMultiplier = 0.1;
	char isNegativeValue = 0;

	if (next == delimiter) // Handle empty values
	{
		return 0;
	}

	if(next == '-') // Handle negative values
	{
		isNegativeValue = 1;
		next = getNextChar();
	}

	while(next != delimiter)
	{
		// Handle dot
		if(next == '.')
		{
			inFraction = 1;
			next = getNextChar();
			continue;
		}

		// Validate digits
		if(!isValidDigit(next))
		{
			*parsedValue = 0;
			return 0;
		}

		if (!inFraction)
		{
			agregateInteger(next, parsedValue);
		}
		else
		{
			agregateFraction(next, parsedValue, fractionMultiplier);
			fractionMultiplier *= 0.1;
		}

		next = getNextChar();
	}

	if(isNegativeValue){
		*parsedValue = -(*parsedValue);
	}

	return 1;
}
