#include "buffer.h"
extern "C" {
    #include <string.h>
}

Buffer:Buffer(uint16_t size): head(0), tail(0), size(size)
{
    data = (uint8_t *) malloc(size);
} 

enum BufferStatus Buffer::read(const uint8_t* data, uint16_t *size)
{
    


}

enum BufferStatus Buffer::readByteFromBuffer(uint8_t *byte) 
{
    if (isBufferEmpty())
    {
        return BUFFER_EMPTY;
    }
    *byte = this->data[head];
    this->head = (this->head + 1) % this->size;
    this->count--;
    return BUFFER_OK;
}

enum BufferStatus Buffer::writeByteToBuffer(uint8_t *byte)
{

}

uint16_t Buffer::getAvailableBytesLeft() const 
{
    return (uint16_t) size - count;
}

