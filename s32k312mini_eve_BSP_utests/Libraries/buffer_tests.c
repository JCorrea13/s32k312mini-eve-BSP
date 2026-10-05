#include "unity.h"
#include <stdio.h>
#include <stdint.h>

#include "../s32k312mini_eve_BSP/src/Libraries/buffer.h"

void test_bufferWrite_WhenValidValue_ReturnsTrueAndRawStorageIsWritten(void)
{
	// Arrange
	unsigned char size = 5;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);
	unsigned char c = 'A';

	// Act
	char result = bufferWrite(&buffer, c);

	// Assert
	TEST_ASSERT_TRUE(result);
	TEST_ASSERT_EQUAL_CHAR(c, raw_storage[0]);
}

void test_bufferWrite_WhenMultipleValues_ReturnsTrueAndRawStorageIsWritten(void)
{
	// Arrange
	unsigned char size = 5;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);
	unsigned char c1 = 'A';
	unsigned char c2 = 'E';

	// Act
	char result1 = bufferWrite(&buffer, c1);
	char result2 = bufferWrite(&buffer, c2);

	// Assert
	TEST_ASSERT_TRUE(result1);
	TEST_ASSERT_TRUE(result2);
	TEST_ASSERT_EQUAL_CHAR(c1, raw_storage[0]);
	TEST_ASSERT_EQUAL_CHAR(c2, raw_storage[1]);
}

void test_bufferWrite_WhenBufferIsFull_ReturnsFalse(void)
{
	// Arrange
	unsigned char size = 1;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);
	unsigned char c1 = 'A';
	unsigned char c2 = 'E';

	// Act
	char result1 = bufferWrite(&buffer, c1);
	char result2 = bufferWrite(&buffer, c2);

	// Assert
	TEST_ASSERT_TRUE(result1);
	TEST_ASSERT_FALSE(result2);
	TEST_ASSERT_EQUAL_CHAR(c1, raw_storage[0]);
}

void test_bufferRead_WhenBufferEmpty_ReturnsFalse(void)
{
	// Arrange
	unsigned char size = 1;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);
	unsigned char c;

	// Act
	char result = bufferRead(&buffer, &c);

	// Assert
	TEST_ASSERT_FALSE(result);
}

void test_bufferRead_WhenReferenceValueIsNull_ReturnFalse(void)
{
	// Arrange
	unsigned char size = 1;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);

	// Act
	bufferWrite(&buffer, 'A');
	char result = bufferRead(&buffer, NULL);

	// Assert
	TEST_ASSERT_FALSE(result);
}

void test_bufferRead_WhenThereIsData_ReturnTrueAndDataMatches(void)
{
	// Arrange
	unsigned char size = 1;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);
	unsigned char c;

	// Act
	bufferWrite(&buffer, 'A');
	char result = bufferRead(&buffer, &c);

	// Assert
	TEST_ASSERT_TRUE(result);
	TEST_ASSERT_EQUAL_CHAR('A', c);
}

void test_bufferRead_WhenMultipleRead_ReturnTrueAndDataMatches(void)
{
	// Arrange
	unsigned char size = 2;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);
	unsigned char c1;
	unsigned char c2;

	// Act
	bufferWrite(&buffer, 'A');
	bufferWrite(&buffer, 'B');
	char result1 = bufferRead(&buffer, &c1);
	char result2 = bufferRead(&buffer, &c2);

	// Assert
	TEST_ASSERT_TRUE(result1);
	TEST_ASSERT_TRUE(result2);
	TEST_ASSERT_EQUAL_CHAR('A', c1);
	TEST_ASSERT_EQUAL_CHAR('B', c2);
}

void test_bufferRead_WhenReadWritesCiclesBuffer_ReturnTrueAndDataMatches(void)
{
	// Arrange
	unsigned char size = 1;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);
	unsigned char c1;
	unsigned char c2;

	// Act
	char result1 = bufferWrite(&buffer, 'A');
	char result2 = bufferRead(&buffer, &c1);
	char result3 = bufferWrite(&buffer, 'B');
	char result4 = bufferRead(&buffer, &c2);

	// Assert
	TEST_ASSERT_TRUE(result1);
	TEST_ASSERT_TRUE(result2);
	TEST_ASSERT_TRUE(result3);
	TEST_ASSERT_TRUE(result4);
	TEST_ASSERT_EQUAL_CHAR('A', c1);
	TEST_ASSERT_EQUAL_CHAR('B', c2);
}

void test_bufferIsEmpty_WhenEmpty_ReturnsTrue(void)
{
	// Arrange
	unsigned char size = 5;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);

	// Act
	char result = bufferIsEmpty(&buffer);

	// Assert
	TEST_ASSERT_TRUE(result);
}

void test_bufferIsEmpty_WhenNotEmpty_ReturnsFalse(void)
{
	// Arrange
	unsigned char size = 5;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);

	// Act
	bufferWrite(&buffer, 'A');
	char result = bufferIsEmpty(&buffer);

	// Assert
	TEST_ASSERT_FALSE(result);
}

void test_bufferIsFull_WhenFull_ReturnsTrue(void)
{
	// Arrange
	unsigned char size = 1;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);

	// Act
	bufferWrite(&buffer, 'A');
	char result = bufferIsFull(&buffer);

	// Assert
	TEST_ASSERT_TRUE(result);
}

void test_bufferIsFull_WhenNotFull_ReturnsFalse(void)
{
	// Arrange
	unsigned char size = 1;
	char_buffer_t buffer;
	unsigned char raw_storage[size];
	bufferInit(&buffer, raw_storage, size);

	// Act
	char result = bufferIsFull(&buffer);

	// Assert
	TEST_ASSERT_FALSE(result);
}

int buffer_tests(void) {
    UNITY_BEGIN();

    RUN_TEST(test_bufferWrite_WhenValidValue_ReturnsTrueAndRawStorageIsWritten);
    RUN_TEST(test_bufferWrite_WhenMultipleValues_ReturnsTrueAndRawStorageIsWritten);
    RUN_TEST(test_bufferWrite_WhenBufferIsFull_ReturnsFalse);
    RUN_TEST(test_bufferRead_WhenBufferEmpty_ReturnsFalse);
    RUN_TEST(test_bufferRead_WhenReferenceValueIsNull_ReturnFalse);
    RUN_TEST(test_bufferRead_WhenThereIsData_ReturnTrueAndDataMatches);
    RUN_TEST(test_bufferRead_WhenMultipleRead_ReturnTrueAndDataMatches);
    RUN_TEST(test_bufferRead_WhenReadWritesCiclesBuffer_ReturnTrueAndDataMatches);
    RUN_TEST(test_bufferIsEmpty_WhenEmpty_ReturnsTrue);
    RUN_TEST(test_bufferIsEmpty_WhenNotEmpty_ReturnsFalse);
    RUN_TEST(test_bufferIsFull_WhenFull_ReturnsTrue);
    RUN_TEST(test_bufferIsFull_WhenNotFull_ReturnsFalse);

    return UNITY_END();
}
