#include "date_parser.h"
#include "../parse_utils.h"

typedef enum
{
	DAY,
	MONTH,
	YEAR,
	FINAL_DELIMITER
} date_state;

const date_t zero_date = { 0 };

char parseDate(char delimiter, getNextCharacter getNextChar, date_t *parsedValue)
{
	*parsedValue = zero_date;
	date_state current_state = DAY;
	uint8_t processed_digits = 0;

	char next = getNextChar();

	while(next != delimiter)
	{
		switch(current_state)
		{
			case DAY:

				if(!isValidDigit(next))
				{
					return 0;
				}

				agregateIntegerToUint8_t(next, &(*parsedValue).day);
				if(++processed_digits >= 2)
				{
					// validate valid range for days
					if ((*parsedValue).day < 0 || (*parsedValue).day > 31)
					{
						return 0;
					}

					processed_digits = 0;
					current_state = MONTH;
				}

				break;
			case MONTH:

				if(!isValidDigit(next))
				{
					return 0;
				}

				agregateIntegerToUint8_t(next, &(*parsedValue).month);
				if(++processed_digits >= 2)
				{
					// validate valid range for months
					if ((*parsedValue).month < 0 || (*parsedValue).month > 12)
					{
						return 0;
					}

					processed_digits = 0;
					current_state = YEAR;
				}

				break;
			case YEAR:

				if(!isValidDigit(next))
				{
					return 0;
				}

				agregateIntegerToUint8_t(next, &(*parsedValue).year);
				if(++processed_digits >= 2)
				{
					// validate valid range for years
					if ((*parsedValue).year < 0)
					{
						return 0;
					}

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

