#include "NMEA_types_parser.h"

typedef enum
{
	IDLE,
	GP1,
	GP2,
	GP3,
	RMC1,
	RMC2,
	RMC3,
	GGA1,
	GGA2,
	GGA3
} nmea_state;

NMEA_setntece_type parseNMEASentenceType(getNextCharacter getNextChar)
{
	nmea_state current_state = IDLE;
	char next = getNextChar();

	while(next != '\0')
	{
		switch(current_state)
		{
			case IDLE:
				if(next == '$')
				{
					current_state = GP1;
				}
				break;
			case GP1:
				if(next == 'G' || next == 'g')
				{
					current_state = GP2;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case GP2:
				if(next == 'P' || next == 'p')
				{
					current_state = GP3;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case GP3:
				if(next == 'R' || next == 'r')
				{
					current_state = RMC1;
				}
				else if(next == 'G' || next == 'g')
				{
					current_state = GGA1;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case RMC1:
				if(next == 'M' || next == 'm')
				{
					current_state = RMC2;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case RMC2:
				if(next == 'C' || next == 'c')
				{
					current_state = RMC3;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case RMC3:
				if(next == ',')
				{
					return GPRMC;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case GGA1:
				if(next == 'G' || next == 'g')
				{
					current_state = GGA2;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case GGA2:
				if(next == 'A' || next == 'a')
				{
					current_state = GGA3;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			case GGA3:
				if(next == ',')
				{
					return GPGGA;
				}
				else
				{
					current_state = IDLE;
				}
				break;
			default:
				current_state = IDLE;
		}

		next = getNextChar();
	}

	return UNKNOWN;
}
