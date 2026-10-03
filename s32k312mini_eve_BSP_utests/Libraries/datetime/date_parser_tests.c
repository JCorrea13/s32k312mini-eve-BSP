#include "unity.h"
#include <stdio.h>
#include <stdint.h>

#include "../s32k312mini_eve_BSP/src/Libraries/datetime/date_parser.h"

static char *date_input = "";
static int current_date_index = 0;

static char getNextDateCharMock()
{
	return date_input[current_date_index++];
}

void test_parseDate_WhenEmptyValue_ReturnsFalse(void)
{
	// Arrange
	date_input = "";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidValue_ReturnsFalse(void)
{
	// Arrange
	date_input = "ASDFGG;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidValue2_ReturnsFalse(void)
{
	// Arrange
	date_input = "1005207;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidValue3_ReturnsFalse(void)
{
	// Arrange
	date_input = "-78956;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidValue4_ReturnsFalse(void)
{
	// Arrange
	date_input = "123.78;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidValue5_ReturnsFalse(void)
{
	// Arrange
	date_input = "-123.78;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidValue6_ReturnsFalse(void)
{
	// Arrange
	date_input = "45DT68;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidValue7_ReturnsFalse(void)
{
	// Arrange
	date_input = "0101269;"; // Unexpected size of date
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidDay_ReturnsFalse(void)
{
	// Arrange
	date_input = "320526;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidMonth_ReturnsFalse(void)
{
	// Arrange
	date_input = "011326;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenInvalidYear_ReturnsFalse(void)
{
	// Arrange
	date_input = "0101A9;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_FALSE(isValidValue);
}

void test_parseDate_WhenValidDate_ReturnsTrueAndValuesMatch(void)
{
	// Arrange
	date_input = "200595;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(isValidValue);
	TEST_ASSERT_EQUAL_INT(20, result.day);
	TEST_ASSERT_EQUAL_INT(5, result.month);
	TEST_ASSERT_EQUAL_INT(95, result.year);
}

void test_parseDate_WhenValidDate2_ReturnsTrueAndValuesMatch(void)
{
	// Arrange
	date_input = "310349;";
	current_date_index = 0;
	date_t result = { 0 };

	// Act
	char isValidValue = parseDate(';', getNextDateCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(isValidValue);
	TEST_ASSERT_EQUAL_INT(31, result.day);
	TEST_ASSERT_EQUAL_INT(3, result.month);
	TEST_ASSERT_EQUAL_INT(49, result.year);
}

int date_parser_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parseDate_WhenEmptyValue_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidValue_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidValue2_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidValue3_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidValue4_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidValue5_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidValue6_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidDay_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidMonth_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenInvalidYear_ReturnsFalse);
    RUN_TEST(test_parseDate_WhenValidDate_ReturnsTrueAndValuesMatch);
    RUN_TEST(test_parseDate_WhenValidDate2_ReturnsTrueAndValuesMatch);

    return UNITY_END();
}
