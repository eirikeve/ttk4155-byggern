#pragma once
#include <stdint.h>

enum BufferStatus
{
    BUFFER_OK,
    BUFFER_EMPTY,
    BUFFER_FULL
};

class Buffer
{
  public:
    /*
    @param size: size of buffer, must be a power of 2
    */
    Buffer(uint16_t size);
    enum BufferStatus read(const uint8_t *data, uint16_t size);
    enum BufferStatus write(uint8_t *data, uint16_t size);
    enum BufferStatus writeByteToBuffer(uint8_t *byte);
    enum BufferStatus readByteFromBuffer(uint8_t *byte);
    uint16_t getAvailableBytesLeft() const;
    bool isBufferEmpty() const;
    bool isBufferFull() const;
    void flushBuffer(const bool clearBuffer);

  private:
    uint8_t *data;
    uint16_t head;
    uint16_t tail;
    uint16_t size;
};