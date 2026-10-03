#include "unity.h"
#include <stdio.h>
#include <stdint.h>

#include "../s32k312mini_eve_BSP/src/Libraries/math/integer_parser.h"

static char *integer_input = "";
static int current_int_index = 0;

static char getNextIntegerCharMock()
{
	return integer_input[current_int_index++];
}

void test_parseUint8t_WhenValidIngegerValue_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	integer_input = "152;";
	current_int_index = 0;
	uint8_t result = 0;

	// Act
	char isValidValue = parseUint8_t(';', getNextIntegerCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_INT(152, result);
}

void test_parseUint8t_WhenInvalidValue_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	integer_input = "12ASDF;";
	current_int_index = 0;
	uint8_t result = 0;

	// Act
	char isValidValue = parseUint8_t(';', getNextIntegerCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseUint8t_WhenInvalidValue2_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	integer_input = "12.650.23";
	current_int_index = 0;
	uint8_t result = 0;

	// Act
	char isValidValue = parseUint8_t(';', getNextIntegerCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseUint8t_WhenInvalidValue3_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	integer_input = "-123";
	current_int_index = 0;
	uint8_t result = 0;

	// Act
	char isValidValue = parseUint8_t(';', getNextIntegerCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseUint8t_WhenEmptyValue_ReturnsFalseAndValueIsZero(void)
{
	// Arrange
	integer_input = "";
	current_int_index = 0;
	uint8_t result = 0;

	// Act
	char isValidValue = parseUint8_t(';', getNextIntegerCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(0 == isValidValue);
	TEST_ASSERT_EQUAL_DOUBLE(0, result);
}

void test_parseUint8t_WhenDelimiterIsEndOfString_ReturnsTrueAndValueMatch(void)
{
	// Arrange
	integer_input = "123";
	current_int_index = 0;
	uint8_t result = 0;

	// Act
	char isValidValue = parseUint8_t('\0', getNextIntegerCharMock, &result);

	// Assert
	TEST_ASSERT_TRUE(1 == isValidValue);
	TEST_ASSERT_EQUAL_INT(123, result);
}

int integer_parser_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_parseUint8t_WhenValidIngegerValue_ReturnsTrueAndValueMatch);
    RUN_TEST(test_parseUint8t_WhenInvalidValue_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseUint8t_WhenInvalidValue2_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseUint8t_WhenInvalidValue3_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseUint8t_WhenEmptyValue_ReturnsFalseAndValueIsZero);
    RUN_TEST(test_parseUint8t_WhenDelimiterIsEndOfString_ReturnsTrueAndValueMatch);

    return UNITY_END();
}
