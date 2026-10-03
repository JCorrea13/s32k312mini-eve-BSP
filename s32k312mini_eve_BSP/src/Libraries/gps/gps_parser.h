/**
 * @file gps_parser.h
 * @brief This file exposes utility functions to parse GPS NMEA sentences.
 */
#if !defined(gps_parser_)
#define gps_parser_

#include <stdint.h>
#include "NMEA_types_parser.h"
#include "../math/double_parser.h"
#include "../math/float_parser.h"
#include "../datetime/date_parser.h"
#include "../datetime/time_parser.h"

typedef char (getNextCharacter)(void);

typedef struct
{
	char success;
	time_t time;
	char status;
	double latitud;
	char latitud_hemisphere;
	double longitude;
	char longitude_hemisphere;
	float speed_over_ground;
	float track_angle;
	date_t date;
	float magnetic_variation;
	char direction_of_variation;
	char mode_indicator;
	uint8_t data_integrity_check;
	uint8_t fix_quality;
	uint8_t number_of_satellites_currently_tracked;
	float horizontal_dilution_of_precision;
	double antenna_altitude;
} GPS_Result;

typedef void (gpsParserCallback)(GPS_Result result);

/**
 * Parses a GPS Sentence.
 * @getNextChar A function to get the next character.
 * @sentence The NMEA sentence type to be parsed.
 *
 * @return a GPS_Result with the parsed data.
 */
GPS_Result parseGPS(getNextCharacter getNextChar, NMEA_setntece_type sentence);

#endif
