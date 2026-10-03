#include "time_parser.h"
#include "../parse_utils.h"

typedef enum
{
	HOUR,
	MINUTES,
	SECONDS,
	DOT,
	MILLISECONDS,
	FINAL_DELIMITER
} time_state;

const time_t zero_time = { 0 };

char parseTime(char delimiter, getNextCharacter getNextChar, time_t *parsedValue)
{
	*parsedValue = zero_time;
	time_state current_state = HOUR;
	uint8_t processed_digits = 0;

	char next = getNextChar();

	while(next != delimiter)
	{
		switch(current_state)
		{
			case HOUR:

				if(!isValidDigit(next))
				{
					return 0;
				}

				agregateIntegerToUint8_t(next, &(*parsedValue).hour);
				if(++processed_digits >= 2)
				{
					// validate valid range for hours
					if ((*parsedValue).hour < 0 || (*parsedValue).hour > 23)
					{
						return 0;
					}

					processed_digits = 0;
					current_state = MINUTES;
				}

				break;
			case MINUTES:

				if(!isValidDigit(next))
				{
					return 0;
				}

				agregateIntegerToUint8_t(next, &(*parsedValue).minutes);
				if(++processed_digits >= 2)
				{
					// validate valid range for minutes
					if ((*parsedValue).minutes < 0 || (*parsedValue).minutes > 59)
					{
						return 0;
					}

					processed_digits = 0;
					current_state = SECONDS;
				}

				break;
			case SECONDS:

				if(!isValidDigit(next))
				{
					return 0;
				}

				agregateIntegerToUint8_t(next, &(*parsedValue).seconds);
				if(++processed_digits >= 2)
				{
					// validate valid range for seconds
					if ((*parsedValue).seconds < 0 || (*parsedValue).seconds > 59)
					{
						return 0;
					}

					processed_digits = 0;
					current_state = DOT;
				}

				break;
			case DOT:

				if(next == '.')
				{
					current_state = MILLISECONDS;
				}
				else
				{
					return 0;
				}

				break;
			case MILLISECONDS:

				if(!isValidDigit(next))
				{
					return 0;
				}

				agregateIntegerToUint8_t(next, &(*parsedValue).milliseconds);
				if(++processed_digits >= 2)
				{
					processed_digits = 0;
					current_state = FINAL_DELIMITER;
				}

				break;
			default:
				return 0;
		}

		next = getNextChar();
	}

	return current_state == FINAL_DELIMITER;
}

