#include "unity.h"
#include <stdio.h>
#include <stdint.h>

#include "../s32k312mini_eve_BSP/src/Libraries/datetime/time_parser.h"

static char *time_input = "";
static int current_time_index = 0;

static char getNextTimeCharMock()
{
	return time_input[current_time_index++];
}

void test_parseTime_WhenValidEmptyValue_ReturnsFalse(void)
{
	// Arrange
	time_input = "";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidValue_ReturnsFalse(void)
{
	// Arrange
	time_input = "ASDF";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidValue2_ReturnsFalse(void)
{
	// Arrange
	time_input = "1234AS";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidValue3_ReturnsFalse(void)
{
	// Arrange
	time_input = "061206;";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidValue4_ReturnsFalse(void)
{
	// Arrange
	time_input = "061206.123;";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidValue5_ReturnsFalse(void)
{
	// Arrange
	time_input = "-61206;";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidHourValue_ReturnsFalse(void)
{
	// Arrange
	time_input = "240000.00;";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidMinutesValue_ReturnsFalse(void)
{
	// Arrange
	time_input = "236000.00;";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenInvalidSecodsValue_ReturnsFalse(void)
{
	// Arrange
	time_input = "230060.00;";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseTime_WhenValidTime_ReturnsTrueAndValuesMatch(void)
{
	// Arrange
	time_input = "233015.57;";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime(';', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(isValidValue);
	TEST_ASSERT_EQUAL_INT(23, result.hour);
	TEST_ASSERT_EQUAL_INT(30, result.minutes);
	TEST_ASSERT_EQUAL_INT(15, result.seconds);
	TEST_ASSERT_EQUAL_INT(57, result.milliseconds);
}

void test_parseTime_WhenDelimiterIsEndOfString_ReturnsTrueAndValuesMatch(void)
{
	// Arrange
	time_input = "233015.57";
	current_time_index = 0;
	time_t result = { 0 };

	// Act
	char isValidValue = parseTime('\0', getNextTimeCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(isValidValue);
	TEST_ASSERT_EQUAL_INT(23, result.hour);
	TEST_ASSERT_EQUAL_INT(30, result.minutes);
	TEST_ASSERT_EQUAL_INT(15, result.seconds);
	TEST_ASSERT_EQUAL_INT(57, result.milliseconds);
}

int time_parser_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parseTime_WhenValidEmptyValue_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidValue_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidValue2_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidValue3_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidValue4_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidValue5_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidHourValue_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidMinutesValue_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenInvalidSecodsValue_ReturnsFalse);
    RUN_TEST(test_parseTime_WhenValidTime_ReturnsTrueAndValuesMatch);
    RUN_TEST(test_parseTime_WhenDelimiterIsEndOfString_ReturnsTrueAndValuesMatch);

    return UNITY_END();
}
