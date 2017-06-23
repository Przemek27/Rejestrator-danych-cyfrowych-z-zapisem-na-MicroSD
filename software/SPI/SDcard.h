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
 * @param response - response from SD Card
 * @param response_length - response length in bytes
 * */
void sdCard_SendCommand(alt_u8 *command, alt_u32 *response, alt_u8 response_length);

#endif /* SDCARD_H_ */
