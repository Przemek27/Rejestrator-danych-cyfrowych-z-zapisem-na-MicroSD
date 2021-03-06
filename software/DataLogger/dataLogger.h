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
#define SD_CARD_LOGGER_START_ADDRESS 4096

/*structure contains data logger's status flags and buffer*/
typedef struct{
	alt_u8 dataAcquire_Flag;		//flag set - read data from GPIO
	alt_u8 dataDump_Flag;			//flag set - send log data to PC
	alt_u8 dataSaveToSD_Flag;		//flag set - save data to SD Card
	alt_u8 freqChange_Flag;			//flag set - user wants to change sampling rate
	alt_u8 buffer1[512];
	alt_u8 buffer2[512];
	alt_u32 bufIndex;
	alt_u8 activeBuffer;			//index of active buffer (1 or 2)
	alt_u32 dataDestinationAddr; 	//address of SD Card where data will be stored
	alt_u32 bufSaved;				//number of buffers saved to SD Card
}DataLogger;

/*
 * @param logger - structure contains data logger's status flags*/
void dataLogger_manage(DataLogger *logger);

/*
 * Function initializes DataLogger structure with default values*/
void dataLogger_init(DataLogger *logger);

#endif /* DATALOGGER_H_ */
