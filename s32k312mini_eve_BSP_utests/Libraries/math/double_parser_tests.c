#include "unity.h"
#include <stdio.h>

#include "../s32k312mini_eve_BSP/src/Libraries/math/double_parser.h"

static char *input = "";
static int currentIndex = 0;

void setUp(void)
{
	input = "";
	currentIndex = 0;
}

void tearDown(void) {}

static char getNextCharMock()
{
	return input[currentIndex++];
}

void test_parseDouble_WhenValidIngegerOnlyValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	input = "1525;";
	double result = 0.0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE((double)1525, result);
}

void test_parseDouble_WhenValidFractionOnlyValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	input = ".1562;";
	double result = 0.0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0.1562, result);
}

void test_parseDouble_WhenValidValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	input = "1545.8965;";
	double result = 0.0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(1545.8965, result);
}

void test_parseDouble_WhenValidnNegativeValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	input = "-1545.8965;";
	double result = 0.0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(-1545.8965, result);
}

void test_parseDouble_WhenInvalidValue_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	input = "12ASDF;";
	double result = 0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseDouble_WhenInvalidValue2_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	input = "12.650.23";
	double result = 0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseDouble_WhenInvalidValue3_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	input = "12..23";
	double result = 0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseDouble_WhenInvalidValue4_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	input = "--123.78925";
	double result = 0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseDouble_WhenEmptyValue_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	input = "";
	double result = 0;

	// Act
	char isValidValue = parseDouble(';', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseDouble_WhenDelimiterIsEndOfString_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	input = "1235";
	double result = 0;

	// Act
	char isValidValue = parseDouble('\0', getNextCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(1235, result);
}

int double_parser_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parseDouble_WhenValidIngegerOnlyValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseDouble_WhenValidFractionOnlyValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseDouble_WhenValidValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseDouble_WhenValidnNegativeValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseDouble_WhenInvalidValue_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseDouble_WhenInvalidValue2_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseDouble_WhenInvalidValue3_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseDouble_WhenInvalidValue4_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseDouble_WhenEmptyValue_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseDouble_WhenDelimiterIsEndOfString_ReturnsTrueAndValueMatch);

    return UNITY_END();
}
