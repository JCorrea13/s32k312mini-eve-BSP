#include "gps_parser.h"

typedef enum
{
	IDLE,
	PARSE_GPRMC,
	PARSE_GPGGA,
	COMPLETE
} state;

static char parseStatus(char delimiter, getNextCharacter getNextChar, char *status)
{
	char next = getNextChar();
	char charCount = 0;

	*status = next;
	while(next != delimiter)
	{
		charCount++;
		next = getNextChar();
	}

	return (*status == 'A' || *status == 'V') && charCount == 1;
}

static char parseLatitudHemisphere(char delimiter, getNextCharacter getNextChar, char *hemisphere)
{
	char next = getNextChar();
	char charCount = 0;

	*hemisphere = next;
	while(next != delimiter)
	{
		charCount++;
		next = getNextChar();
	}

	return (*hemisphere == 'N' || *hemisphere == 'S') && charCount == 1;
}

static char parseLontitudHemisphere(char delimiter, getNextCharacter getNextChar, char *hemisphere)
{
	char next = getNextChar();
	char charCount = 0;

	*hemisphere = next;
	while(next != delimiter)
	{
		charCount++;
		next = getNextChar();
	}

	return (*hemisphere == 'E' || *hemisphere == 'W') && charCount == 1;
}

GPS_Result parseGPS(getNextCharacter getNextChar, NMEA_setntece_type sentence)
{
	state current_state;
	current_state = IDLE;

	GPS_Result result;
	result.success = 0;

	while(1)
	{
		switch(current_state)
		{
			case IDLE:
				{
					NMEA_setntece_type sentence_type = parseNMEASentenceType(getNextChar);

					if(sentence_type != sentence)
					{
						current_state = IDLE;
					}

					if (GPRMC == sentence)
					{
						current_state = PARSE_GPRMC;
					}
					else if(GPGGA == sentence)
					{
						current_state = PARSE_GPGGA;
					}

					break;
				}
			case PARSE_GPRMC:
				result.success = parseTime(',', getNextChar, &result.time);
				result.success &= parseStatus(',', getNextChar, &result.status);
				result.success &= parseDouble(',', getNextChar, &result.latitud);
				result.success &= parseLatitudHemisphere(',', getNextChar, &result.latitud_hemisphere);
				result.success &= parseDouble(',', getNextChar, &result.longitude);
				result.success &= parseLontitudHemisphere(',', getNextChar, &result.longitude_hemisphere);
				result.success &= parseFloat(',', getNextChar, &result.speed_over_ground);
				result.success &= parseFloat(',', getNextChar, &result.track_angle);
				result.success &= parseDate(',', getNextChar, &result.date);
				result.success &= parseFloat(',', getNextChar, &result.magnetic_variation);
				result.success &= parseLontitudHemisphere(',', getNextChar, &result.direction_of_variation);
				return result;
			case PARSE_GPGGA:
				break;
			default:
				break;
		}
	}

	return result;

}
