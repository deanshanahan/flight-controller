/*****************************************************************************
* FILENAME:     i2c.h
*
* AUTHOR :      Dean Shanahan
*
* DESCRIPTION :
*   Library for sending data to the I2C bus of the ATMega328P.
*
* FUNCTIONS :
*   void        i2c_init_master         (void)
*   uint8_t     i2c_start               (void)
*   uint8_t     i2c_repeated_start      (void)
*   uint8_t     i2c_WR_addr             (unsigned char addr)
*   uint8_t     i2c_RD_addr             (unsigned char addr)
*   uint8_t     i2c_WR_data             (unsigned char data)
*   uint8_t     i2c_RD_NACK_data        (void)
*   uint8_t     i2c_RD_ACK_data         (void)
*   void        i2c_stop                (void)
*
* NOTES :
*   -   Atmel refers to i2c as TWI (Two Wire Interface)
*   -   TWI is outlined on the ATMega datasheet in chapter 19
*
*/

#ifndef _I2C_H_
#define _I2C_H_

// Define ATMega328P clock speed of 16MHz if not defined
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

// Define SCL clock speed of 100kHz if not defined
#ifndef F_SCL
#define F_SCL 100000UL
#endif

// Set the clock prescaler for i2c and set the TWI Bit Rate Register (TWBR)
#define PRESCALER 1
#define TWBR_VAL ((((F_CPU / F_SCL) / PRESCALER) - 16 ) / 2)

// Define read/write variables for i2c
#define I2C_RD	0x01
#define I2C_WR	0x00

// Libraries included
#include <stdint.h>

// Functions 
void i2c_init_master(void);
uint8_t  i2c_start(void);
uint8_t  i2c_repeated_start(void);
uint8_t  i2c_WR_addr( unsigned char addr );
uint8_t  i2c_RD_addr( unsigned char addr );
uint8_t  i2c_WR_data( unsigned char data );
uint8_t  i2c_RD_NACK_data(void);
uint8_t  i2c_RD_ACK_data(void);
void i2c_stop(void);

#endif /* _I2C_H_ */
