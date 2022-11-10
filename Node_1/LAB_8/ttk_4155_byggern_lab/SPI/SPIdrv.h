/*
 * SPIdrv.h
 *
 * Created: 06.10.2022 10:20:54
 *  Author: haavarok
 */ 

#ifndef SPIDRV_H_
#define SPIDRV_H_

#include "../MISC/common_includes.h"

#define SPI_DUMMY_DATA 0xf4

void SPI_init(void);
void SPI_transmit(char cData);
void SPI_write(uint8_t data);
uint8_t SPI_read();

#endif /* SPIDRV_H_ */
