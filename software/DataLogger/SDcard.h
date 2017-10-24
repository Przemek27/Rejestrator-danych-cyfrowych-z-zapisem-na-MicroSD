/*
 * SDcard.h
 *
 *  Created on: 29 maj 2017
 *      Author: Przemek
 */

#ifndef SDCARD_H_
#define SDCARD_H_

#include "alt_types.h"

#define MAX_RESPONSE_LENGTH 5

void delay(void);

/*@return 0 - Initialization failed
 * 		  1 - Initialization successful
 *
 * Function initiates SD Card in SPI mode*/
alt_u8 sdCard_Init(void);

/*
 * @param command - command send to SD Card
 * @param response - expected response from SD Card
 * @param response_length - expected response length in bytes
 * */
void sdCard_SendCommand(alt_u8 *command, alt_u32 *response, alt_u8 response_length);

/*
 * @param address - read from address
 * @param blocks - number of blocks to read (block = 512 B)
 * @param buffer - data will be stored in buffer
 * */
void sdCard_ReadData(alt_u32 address, alt_u8  blocks, alt_u8 *buffer);

/*
 * @param address - where to save data
 * @param *data
 * */
void sdCard_SaveData(alt_u32 address, alt_u8 *data);

#endif /* SDCARD_H_ */
