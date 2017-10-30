// #include "buffer.h"
// extern "C" {
// #include <assert.h>
// #include <string.h>
// }

// Buffer::Buffer(uint16_t size) : head(0), tail(0), size(size)
// {
//     // Check that size is a power of 2
//     assert((size != 0) && ((size & (size - 1)) == 0));
//     data = (uint8_t *)malloc(size);
// }

// enum BufferStatus Buffer::read(const uint8_t *data, uint16_t size)
// {
// }
// // enum BufferStatus Buffer::read(const uint8_t *data, uint16_t size) {}

// enum BufferStatus Buffer::readByteFromBuffer(uint8_t *byte)
// {
//     if (isBufferEmpty())
//     {
//         return BUFFER_EMPTY;
//     }
//     // memcpy(byte, this->data[tail], 1);
//     // *byte = this->data[head];
//     this->tail = (this->tail + 1) % this->size;
//     return BUFFER_OK;
// }

// enum BufferStatus Buffer::writeByteToBuffer(uint8_t *byte)
// {
//     if (isBufferFull())
//     {
//         return BUFFER_FULL;
//     }
//     // memcpy(this->data[this->head], byte, 1);
//     this->head = (this->head + 1) % this->size;
//     return BUFFER_OK;

//     // this->data[this->head] = *byte;
// }

// uint16_t Buffer::getAvailableBytesLeft() const
// {
//     // return (uint16_t)size - count;
//     return (uint16_t)((this->tail - this->head) + (-((uint16_t)(this->tail <= this->head)) & this->size));
// }

// bool Buffer::isBufferEmpty() const
// {
//     return this->head == this->tail;
// }

// bool Buffer::isBufferFull() const
// {
//     return (this->tail + 1) % this->size == this->head;
// }

// void Buffer::flushBuffer(const bool clearBuffer)
// {
//     this->head = this->tail;
//     if (clearBuffer)
//     {
//         memset(this->data, 0, this->size);
//     }
// }
