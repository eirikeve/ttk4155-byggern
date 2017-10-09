#pragma once

uint8_t mcp2515_init();
uint8_t mcp2515_read(uint8_t address);
void mcp2515_write();
void mcp2515_request_to_send();
void mcp2515_bit_modify();
void mcp2515_reset();
void mcp_read_status();