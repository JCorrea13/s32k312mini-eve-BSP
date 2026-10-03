#include "unity.h"
#include <stdio.h>

#include "../s32k312mini_eve_BSP/src/Libraries/gps/NMEA_types_parser.h"

static char *nmea_input = "";
static int current_index_nmea = 0;

static char getNextNMEACharMock()
{
	return nmea_input[current_index_nmea++];
}

void test_parseNMEASentenceType_WhenEmpty_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenInvalidString_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "ASDFGRE";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenUnknowSentence_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "$GPQWER";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenUnknowSentence2_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "$GPRMZ";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenUnknowSentence3_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "$GPRZZ";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenUnknowSentence4_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "$GPGZZ";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenUnknowSentence5_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "$GPGGZ";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenUnknowSentence6_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "$GPRMCZ";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenUnknowSentence7_ReturnsUknown(void)
{
	// Arrange
	nmea_input = "$GPGGAZ";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(UNKNOWN == result);
}

void test_parseNMEASentenceType_WhenGPRMC_ReturnsGPRMC(void)
{
	// Arrange
	nmea_input = "$GPRMC,";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(GPRMC == result);
}

void test_parseNMEASentenceType_WhenGPGGA_ReturnsGPGGA(void)
{
	// Arrange
	nmea_input = "$GPGGA,";
	current_index_nmea = 0;

	// Act
	NMEA_setntece_type result = parseNMEASentenceType(getNextNMEACharMock);

	// Assert
	TEST_ASSERT_TRUE(GPGGA == result);
}

int NMEA_types_parser_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parseNMEASentenceType_WhenEmpty_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenInvalidString_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenUnknowSentence_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenUnknowSentence2_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenUnknowSentence3_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenUnknowSentence4_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenUnknowSentence5_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenUnknowSentence6_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenUnknowSentence7_ReturnsUknown);
    RUN_TEST(test_parseNMEASentenceType_WhenGPRMC_ReturnsGPRMC);
    RUN_TEST(test_parseNMEASentenceType_WhenGPGGA_ReturnsGPGGA);

    return UNITY_END();
}
