/**
 * @file NMEA_types_parser.h
 * @brief This file exposes utility functions to parse GPS NMEA types.
 */
#if !defined(NMEA_types_parser_)
#define NMEA_types_parser_

typedef char (getNextCharacter)(void);

/**
 * Enumeration that represent the different NMEA sentences.
 */
typedef enum
{
	GPRMC,
	GPGGA,
	UNKNOWN
} NMEA_setntece_type;

/**
 * Parses the NMEA sentence type.
 * @return the corresponding NMEA type.
 */
NMEA_setntece_type parseNMEASentenceType(getNextCharacter getNextChar);

#endif
