#include "buffer.h"
#include <stddef.h>

void bufferInit(char_buffer_t *cb, unsigned char *buffer, size_t size)
{
	 cb->buffer = buffer;
	 cb->size = size;
	 cb->head = 0;
	 cb->tail = 0;
	 cb->count = 0;
}

char bufferWrite(char_buffer_t *buffer, unsigned char c)
{
	if (bufferIsFull(buffer))
	{
		return 0;
	}

	buffer->buffer[buffer->head] = c;
	buffer->head = (buffer->head + 1) % buffer->size;
	buffer->count++;

	return 1;
}

char bufferRead(char_buffer_t *buffer, unsigned char *c)
{
	if (bufferIsEmpty(buffer) || NULL == c)
	{
		return 0;
	}

	*c = buffer->buffer[buffer->tail];
	buffer->tail = (buffer->tail + 1) % buffer->size;
	buffer->count--;

	return 1;
}

char bufferIsEmpty(char_buffer_t *buffer)
{
	return 0 == buffer->count;
}

char bufferIsFull(char_buffer_t *buffer)
{
	return buffer->count == buffer->size;
}
