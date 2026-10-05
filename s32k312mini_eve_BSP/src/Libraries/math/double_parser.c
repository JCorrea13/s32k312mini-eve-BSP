#include "double_parser.h"
#include "../parse_utils.h"

static inline void agregateInteger(char value, double *parsedValue)
{
	char intValue = (int)value - 48;
	*parsedValue = (*parsedValue * 10) + intValue;
}

static inline void agregateFraction(char value, double *parsedValue, double multiplier)
{
	char intValue = (int)value - 48;
	*parsedValue = (*parsedValue) + (intValue * multiplier);
}

char parseDouble(char delimiter, getNextCharacter getNextChar, double *parsedValue)
{
	*parsedValue = 0;
	char next = getNextChar();

	char inFraction = 0;
	double fractionMultiplier = 0.1;
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
