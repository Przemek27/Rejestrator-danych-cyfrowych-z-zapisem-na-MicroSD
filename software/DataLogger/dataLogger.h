/*
 * dataLogger.h
 *
 *  Created on: 25 wrz 2017
 *      Author: Przemek
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include "alt_types.h"

//Address where log will be saved
//TODO: #define SD_CARD_LOGGER_START_ADDRESS

/*structure contains data logger's status flags and buffer*/
typedef struct{
	alt_u8 dataAcquire;			//flag set - read data from GPIO
	alt_u8 dataDump;			//flag set - send log data to PC
	alt_u8 dataSaveToSD;		//flag set - save data to SD Card
	alt_u8 freqChange;			//flag set - user wants to change sampling rate
	alt_u8 buffer1[512];
	alt_u8 buffer2[512];
	alt_u8 activeBuffer;
	alt_u32 bufIndex;
}DataLogger;

/*
 * @param logger - structure contains data logger's status flags*/
void dataLogger_manage(DataLogger *logger);

/*
 * Function initializes DataLogger structure with default values*/
void dataLogger_init(DataLogger *logger);

#endif /* DATALOGGER_H_ */
