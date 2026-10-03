#include "unity.h"
#include <stdio.h>

#include "../s32k312mini_eve_BSP/src/Libraries/gps/gps_parser.h"

static char *gps_input = "";
static int currentIndex1 = 0;

static char getNextGpsCharMock()
{
	return gps_input[currentIndex1++];
}

void test_parseGPS_WhenEmpty_ReturnsSuccessFalse(void)
{
	// Arrange
	gps_input = "";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidTime_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,-191410.10,A,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidTime2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,,A,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidTime3_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,ASDGG,A,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidStatus_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,B,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19"; // Status can be either A or V
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_EQUAL_CHAR('B', result.status);
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidStatus2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,AA,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19"; // Status can be either A or V
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidStatus3_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19"; // Status can be either A or V
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLatitud_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,47AA.56340,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLatitud2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,,N,00739.35380,E,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLatitudHemisphere_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,A,00739.35380,E,12.5,145.5,181126,0.4,E,A*19"; // Status can be either A or V
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_EQUAL_CHAR('A', result.status);
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLatitudHemisphere2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,AA,4735.56340,NN,00739.35380,E,12.5,145.5,181126,0.4,E,A*19"; // Status can be either A or V
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLatitudHemisphere3_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,,4735.56340,,00739.35380,E,12.5,145.5,181126,0.4,E,A*19"; // Status can be either A or V
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLongitud_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,AA739.35380,E,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLongitud2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,,E,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLongitudHemisphere_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,00739.35380,A,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_EQUAL_CHAR('A', result.status);
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLongitudHemisphere2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,00739.35380,EE,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidLongitudHemisphere3_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,00739.35380,,12.5,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidSpeedOverGround_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,AA,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidSpeedOverGround2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,,145.5,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidTrackAngle_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,AA,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidTrackAngle2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,,181126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidDate_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,145.5,1811268,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidDate2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,145.5,ASDF,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidDate3_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,145.5,-110126,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidDate4_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,145.5,,0.4,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidMagneticVariation_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,145.5,181126,ADF,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidMagneticVariation2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,11739.35380,E,12.5,145.5,181126,,E,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidDirectionOfVariation_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,A,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_EQUAL_CHAR('A', result.status);
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidDirectionOfVariation2_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,AA,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithInvalidDirectionOfVariation3_ReturnsNotSuccess(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_FALSE(result.success);
}

void test_parseGPS_WhenGPRMCWithValidSentence_ReturnsSuccessAndValuesMatch(void)
{
	// Arrange
	gps_input = "$GPRMC,191410.10,A,4735.56340,N,00739.35380,E,12.5,145.5,181126,0.4,W,A*19";
	currentIndex1 = 0;
	GPS_Result result = { 0 };

	// Act
	result = parseGPS(getNextGpsCharMock, GPRMC);

	// Assert
	TEST_ASSERT_TRUE(result.success);
	TEST_ASSERT_EQUAL_INT(19, result.time.hour);
	TEST_ASSERT_EQUAL_INT(14, result.time.minutes);
	TEST_ASSERT_EQUAL_INT(10, result.time.seconds);
	TEST_ASSERT_EQUAL_INT(10, result.time.milliseconds);
	TEST_ASSERT_EQUAL_CHAR('A', result.status);
	TEST_ASSERT_EQUAL_DOUBLE(4735.56340, result.latitud);
	TEST_ASSERT_EQUAL_CHAR('N', result.latitud_hemisphere);
	TEST_ASSERT_EQUAL_DOUBLE(739.35380, result.longitude);
	TEST_ASSERT_EQUAL_CHAR('E', result.longitude_hemisphere);
	TEST_ASSERT_EQUAL_FLOAT(12.5, result.speed_over_ground);
	TEST_ASSERT_EQUAL_FLOAT(145.5, result.track_angle);
	TEST_ASSERT_EQUAL_INT(18, result.date.day);
	TEST_ASSERT_EQUAL_INT(11, result.date.month);
	TEST_ASSERT_EQUAL_INT(26, result.date.year);
	TEST_ASSERT_EQUAL_FLOAT(0.4, result.magnetic_variation);
	TEST_ASSERT_EQUAL_CHAR('W', result.direction_of_variation);
}

int gps_parser_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parseGPS_WhenEmpty_ReturnsSuccessFalse);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidTime_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidTime2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidTime3_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidStatus_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidStatus2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidStatus3_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLatitud_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLatitud2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLatitudHemisphere_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLatitudHemisphere2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLatitudHemisphere3_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLongitud_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLongitud2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLongitudHemisphere_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLongitudHemisphere2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidLongitudHemisphere3_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidSpeedOverGround_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidSpeedOverGround2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidTrackAngle_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidTrackAngle2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidDate_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidDate2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidDate3_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidDate4_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidMagneticVariation_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidMagneticVariation2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidDirectionOfVariation_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidDirectionOfVariation2_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithInvalidDirectionOfVariation3_ReturnsNotSuccess);
    RUN_TEST(test_parseGPS_WhenGPRMCWithValidSentence_ReturnsSuccessAndValuesMatch);

    return UNITY_END();
}
