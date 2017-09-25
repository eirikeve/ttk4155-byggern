#pragma once

extern "C" {
#include <string.h>
}

class Comm
{
  public:
    void read();
    void readByteFromInputBuffer();
    bool isInputBufferEmpty();
    bool isInputBufferFull();
    void flushInputBuffer();

    void write();
    void writeByteToOutputBuffer();
    bool isOutputBufferEmpty();
    bool isOutputBufferFull();
    void flushOutputBuffer();

  private:
    // uint8_t * inputBuffer;
    // uint16_t inputBufferHead;
    // uint16_t inputBufferTail;
    // uint16_t inputBufferCount;
    // uint16_t inputBufferSize;

    // uint8_t * outputBuffer;
    // uint16_t outputBufferHead;
    // uint16_t outputBufferTail;
    // uint16_t outputBufferCount;
    // uint16_t outputBufferSize;

    // void read(uint8_t * buffer, uint16_t bufferHead, uint16_t bufferTail, \
    //     uint16_t bufferCount uint16_t bufferSize, uint8_t * string, uint16_t size);
    // void write(uint8_t * buffer, uint8_t * string, uint16_t size);
    // void writeByteToBuffer(uint8_t *buffer, uint8_t *byte);
    // void readByteFromBuffer(uint8_t *buffer, uint8_t *byte);
    // bool isBufferEmpty(uint8_t *buffer);
    // bool isBufferFull(uint8_t *buffer);
    // void flushBuffer(uint8_t *buffer);
};
