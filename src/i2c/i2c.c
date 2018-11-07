/*****************************************************************************
* FILENAME:     i2c.c
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

// Libraries included
#include <util/twi.h>
#include <stdint.h>
#include "i2c.h"

// Initialises the controller as a master
void i2c_init_master(void)
{
	TWBR = TWBR_VAL; 
	TWSR = 0x00; // Set prescaler of 1 to F_SCL
}

// Sends a start condition to the bus
uint8_t i2c_start(void)
{
	// Clear interrupt flag, send start condition, enable i2c
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// Wait for end of transmission
	while ( !( TWCR & (1<<TWINT) ) ); // WAITING...
	// Check that the start condition was acknowledged
	if ( (TWSR & 0xF8) != TW_START )
		return 1;	
	else
		return 0;
}

// Sends a repeated start condition to the bus
uint8_t  i2c_repeated_start( void )
{
	// Clear interrupt flag, send start condition, enable i2c
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// Wait for end of transmission
	while ( !( TWCR & (1<<TWINT) ) ); // WAITING...
	// Check that the repeated start condition was acknowledged
	if ( (TWSR & 0xF8) != TW_REP_START )
		return 1;
	else
		return 0;
}

// Sends an address and the write bit to the bus	
uint8_t  i2c_WR_addr( unsigned char addr )
{
	addr = (addr<<1) | I2C_WR; 
	// Load slave address and write bit into data register
	TWDR = addr;
	// Start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// Wait for end of transmission
	while ( !( TWCR & (1<<TWINT) ) ); // WAITING...
	// Check that the device has acknowledged WRITE mode
	if ( (TWSR & 0xF8) != TW_MT_SLA_ACK )
		return 1;
	else
		return 0;	
}

// Sends an address and the read bit to the bus		
uint8_t  i2c_RD_addr( unsigned char addr )
{
	addr = (addr<<1) | I2C_RD; 
	// Load slave address and read bit into data register
	TWDR = addr;
	// Start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// Wait for end of transmission
	while ( !( TWCR & (1<<TWINT) ) ); // WAITING...
	// Check that the device has acknowledged READ mode
	if ( (TWSR & 0xF8) != TW_MR_SLA_ACK )
		return 1;
	else
		return 0;
}

// Writes a byte of data to the bus	
uint8_t  i2c_WR_data( unsigned char data )
{
	TWDR = data; // Load data into data register
	// Start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);
	// Wait for end of transmission
	while ( !( TWCR & (1<<TWINT) ) ); // WAITING...
	// Check that the device has acknowledged WRITE mode
	if ( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
	else
		return 0;
}

// Reads data from the bus and sends NACK		
uint8_t  i2c_RD_NACK_data( void )
{
	// Clear interrupt flag, eanble i2c
	TWCR = (1<<TWINT) | (1<<TWEN);
	// Wait for end of transmission
	while ( !( TWCR & (1<<TWINT) ) ); // WAITING...
	return TWDR;
}

// Reads data from the bus and sends ACK		
uint8_t  i2c_RD_ACK_data( void )
{
	// Clear interrupt flag, enable i2c, send ACK
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	// Wait for end of transmission
	while ( !( TWCR & (1<<TWINT) ) ); // WAITING...
	return TWDR;
}

// Sends stop condition to the bus	
void i2c_stop( void )
{
	// Clear interrupt flag, enable i2c, transmit stop condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// Wait till stop condition is transmitted
	while(!(TWCR & (1<<TWSTO))); // WAITING...
}
