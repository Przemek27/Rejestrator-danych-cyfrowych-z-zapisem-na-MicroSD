/*
 * SPI.h
 *
 *  Created on: 25 maj 2017
 *      Author: Przemek
 */

#ifndef SPI_H_
#define SPI_H_

#include "alt_types.h"
#include <stdbool.h>

void spi_SelectSlave(alt_u32 base, alt_u32 slave);
void spi_DeselectSlave(alt_u32 base, alt_u32 slave);
void spi_SendByte(alt_u32 base, alt_u32 slave, alt_u8 data);
void spi_SendData(alt_u32 base, alt_u32 slave, const alt_u8 *data, alt_u8 length);
bool spi_IsData(alt_u32 base);
alt_u32 spi_ReadData(alt_u32 base);

#endif /* SPI_H_ */
