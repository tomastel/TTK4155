/*
 * SPIdrv.c
 *
 * Created: 06.10.2022 10:21:06
 *  Author: haavarok
 */ 

#include "SPIdrv.h"

void SPI_init(void)
{
	/* Set PB4, MOSI and SCK output. By using "set_bit", we avoid configuring all other bits (?) */
	//DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	set_bit(DDRB, DDB4);
	set_bit(DDRB, DDB5);
	set_bit(DDRB, DDB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	set_bit(PORTB, PB4);
}

void SPI_transmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

void SPI_write(uint8_t data)
{
	SPI_transmit(data);
}

uint8_t SPI_read()
{
	SPI_transmit(SPI_DUMMY_DATA);
	return SPDR;
}
