// #pragma once

// /****************************************************************************
//   TWI Status/Control register definitions
// ****************************************************************************/
// #define TWI_BUFFER_SIZE 4   // Set this to the largest message size that will be sent including address byte.

// #define TWI_TWBR            0x0C        // TWI Bit rate Register setting.
//                                         // Se Application note for detailed 
//                                         // information on setting this value.
// // Not used defines!
// //#define TWI_TWPS          0x00        // This driver presumes prescaler = 00


// /****************************************************************************
//   Bit and byte definitions
// ****************************************************************************/
// #define I2C_READ_BIT  0       // Bit position for R/W bit in "address byte".
// #define I2C_ADR_BITS  1       // Bit position for LSB of the slave address bits in the init byte.

// #define TRUE          1
// #define FALSE         0

// /****************************************************************************
//   I2C State codes
// ****************************************************************************/
// // General I2C Master staus codes                      
// #define I2C_START                  0x08  // START has been transmitted  
// #define I2C_REP_START              0x10  // Repeated START has been transmitted
// #define I2C_ARB_LOST               0x38  // Arbitration lost

// // I2C Master Transmitter staus codes                      
// #define I2C_MTX_ADR_ACK            0x18  // SLA+W has been tramsmitted and ACK received
// #define I2C_MTX_ADR_NACK           0x20  // SLA+W has been tramsmitted and NACK received 
// #define I2C_MTX_DATA_ACK           0x28  // Data byte has been tramsmitted and ACK received
// #define I2C_MTX_DATA_NACK          0x30  // Data byte has been tramsmitted and NACK received 

// // I2C Master Receiver staus codes  
// #define I2C_MRX_ADR_ACK            0x40  // SLA+R has been tramsmitted and ACK received
// #define I2C_MRX_ADR_NACK           0x48  // SLA+R has been tramsmitted and NACK received
// #define I2C_MRX_DATA_ACK           0x50  // Data byte has been received and ACK tramsmitted
// #define I2C_MRX_DATA_NACK          0x58  // Data byte has been received and NACK tramsmitted

// // I2C Slave Transmitter staus codes
// #define I2C_STX_ADR_ACK            0xA8  // Own SLA+R has been received; ACK has been returned
// #define I2C_STX_ADR_ACK_M_ARB_LOST 0xB0  // Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
// #define I2C_STX_DATA_ACK           0xB8  // Data byte in TWDR has been transmitted; ACK has been received
// #define I2C_STX_DATA_NACK          0xC0  // Data byte in TWDR has been transmitted; NOT ACK has been received
// #define I2C_STX_DATA_ACK_LAST_BYTE 0xC8  // Last data byte in TWDR has been transmitted (TWEA = 0); ACK has been received

// // I2C Slave Receiver staus codes
// #define I2C_SRX_ADR_ACK            0x60  // Own SLA+W has been received ACK has been returned
// #define I2C_SRX_ADR_ACK_M_ARB_LOST 0x68  // Arbitration lost in SLA+R/W as Master; own SLA+W has been received; ACK has been returned
// #define I2C_SRX_GEN_ACK            0x70  // General call address has been received; ACK has been returned
// #define I2C_SRX_GEN_ACK_M_ARB_LOST 0x78  // Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned
// #define I2C_SRX_ADR_DATA_ACK       0x80  // Previously addressed with own SLA+W; data has been received; ACK has been returned
// #define I2C_SRX_ADR_DATA_NACK      0x88  // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
// #define I2C_SRX_GEN_DATA_ACK       0x90  // Previously addressed with general call; data has been received; ACK has been returned
// #define I2C_SRX_GEN_DATA_NACK      0x98  // Previously addressed with general call; data has been received; NOT ACK has been returned
// #define I2C_SRX_STOP_RESTART       0xA0  // A STOP condition or repeated START condition has been received while still addressed as Slave

// // I2C Miscellaneous status codes
// #define I2C_NO_STATE               0xF8  // No relevant state information available; I2CNT = 0
// #define I2C_BUS_ERROR              0x00  // Bus error due to an illegal START or STOP condition