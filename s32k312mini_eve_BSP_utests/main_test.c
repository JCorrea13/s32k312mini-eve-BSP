/**
 * Main test file that invokes all the test files.
 */

#include "Libraries/math/integer_parser_tests.c"
#include "Libraries/math/float_parser_tests.c"
#include "Libraries/math/double_parser_tests.c"
#include "Libraries/gps/gps_parser_tests.c"
#include "Libraries/gps/NMEA_types_parser_tests.c"
#include "Libraries/datetime/time_parser_tests.c"
#include "Libraries/datetime/date_parser_tests.c"
#include "Libraries/buffer_tests.c"

int main(void)
{
	integer_parser_tests();
	float_parser_tests();
	double_parser_tests();
	NMEA_types_parser_tests();
	time_parser_tests();
	date_parser_tests();
	gps_parser_tests();
	buffer_tests();

    return 0;
}
