#include "unity.h"
#include <stdio.h>

#include "../s32k312mini_eve_BSP/src/Libraries/math/float_parser.h"

static char *float_input = "";
static int current_float_index = 0;

static char getNextFloatCharMock()
{
	return float_input[current_float_index++];
}

void test_parseFloat_WhenValidIngegerOnlyValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	float_input = "1525;";
	current_float_index = 0;
	float result = 0.0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT((float)1525, result);
}

void test_parseFloat_WhenValidFractionOnlyValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	float_input = ".1562;";
	current_float_index = 0;
	float result = 0.0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(0.1562, result);
}

void test_parseFloat_WhenValidValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	float_input = "154.89;";
	current_float_index = 0;
	float result = 0.0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(154.89, result);
}

void test_parseFloat_WhenValidnNegativeValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	float_input = "-154.89;";
	current_float_index = 0;
	float result = 0.0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(-154.89, result);
}

void test_parseFloat_WhenInvalidValue_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	float_input = "12ASDF;";
	current_float_index = 0;
	float result = 0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(0, result);
}

void test_parseFloat_WhenInvalidValue2_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	float_input = "12.650.23";
	current_float_index = 0;
	float result = 0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(0, result);
}

void test_parseFloat_WhenInvalidValue3_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	float_input = "12..23";
	current_float_index = 0;
	float result = 0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(0, result);
}

void test_parseFloat_WhenInvalidValue4_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	float_input = "--123.78925";
	current_float_index = 0;
	float result = 0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(0, result);
}

void test_parseFloat_WhenEmptyValue_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	float_input = "";
	current_float_index = 0;
	float result = 0;

	// Act
	char isValidValue = parseFloat(';', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(0, result);
}

void test_parseFloat_WhenDelimiterIsEndOfString_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	float_input = "1235";
	current_float_index = 0;
	float result = 0;

	// Act
	char isValidValue = parseFloat('\0', getNextFloatCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_FLOAT(1235, result);
}

int float_parser_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parseFloat_WhenValidIngegerOnlyValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseFloat_WhenValidFractionOnlyValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseFloat_WhenValidValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseFloat_WhenValidnNegativeValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseFloat_WhenInvalidValue_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseFloat_WhenInvalidValue2_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseFloat_WhenInvalidValue3_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseFloat_WhenInvalidValue4_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseFloat_WhenEmptyValue_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseFloat_WhenDelimiterIsEndOfString_ReturnsTrueAndValueMatch);

    return UNITY_END();
}
