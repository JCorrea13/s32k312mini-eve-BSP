/**
 * @file buffer.h
 * @brief This file exposes utility methods to work with buffers.
 */
#if !defined(buffer_)
#define buffer_

#include <stddef.h>

typedef struct
{
	unsigned char *buffer;
	size_t size;
	size_t head;
	size_t tail;
	size_t count;
} char_buffer_t;

/**
 * This function initializes a buffer.
 * @param *cb the pointer to the buffer struct
 * @param *buffer char pointer to the actual buffer
 * @param size the size of the buffer
 */
void bufferInit(char_buffer_t *cb, unsigned char *buffer, size_t size);

/**
 * This function writes a new char to the top of the buffer.
 * @param *cb the pointer to the buffer to be written on.
 * @param c the char to be written.
 *
 * @return a char representing whether the char was successfully written to the buffer.
 * @revalue 1 if the value was written successfully.
 * @revalue 0 if the value failed to be written.
 */
char bufferWrite(char_buffer_t *cb, unsigned char c);

/**
 * This function reads a char from the bottom of the buffer.
 * @param *cb the pointer to the buffer to be read from.
 * @param c the pointer to the char where the read value will be stored.
 *
 * @return a char representing whether the char was successfully read from the buffer.
 * @revalue 1 if the value was read successfully.
 * @revalue 0 if the value failed to be read.
 */
char bufferRead(char_buffer_t *cb, unsigned char *c);

/**
 * This function validates if there is data in the buffer.
 * @param *cb the pointer to the buffer to be read from.
 *
 * @return a char representing whether there is data in the buffer or not.
 * @revalue 1 if there is data.
 * @revalue 0 if there is no data.
 */
char bufferIsEmpty(char_buffer_t *cb);

/**
 * This function validates if the buffer is full.
 * @param *cb the pointer to the buffer to be read from.
 *
 * @return a char representing whether the buffer is full or not.
 * @revalue 1 if the buffer is full.
 * @revalue 0 if the buffer is not full.
 */
char bufferIsFull(char_buffer_t *cb);

#endif
