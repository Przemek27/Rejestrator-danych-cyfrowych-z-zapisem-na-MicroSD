/*
 * dataLogger.c
 *
 *  Created on: 25 wrz 2017
 *      Author: Przemek
 */

#include "dataLogger.h"
#include "SDcard.h"
#include "sys/alt_stdio.h"

void dataLogger_manage(DataLogger *logger){
	if(logger->dataSaveToSD_Flag == 0xff){
		if(logger->activeBuffer == 1)
			sdCard_SaveData(logger->dataDestinationAddr, logger->buffer1);
		else if(logger->activeBuffer == 2)
			sdCard_SaveData(logger->dataDestinationAddr, logger->buffer2);

		logger->dataSaveToSD_Flag = 0x00;
		logger->bufSaved += 1;
		logger->dataDestinationAddr += 512;
		logger->activeBuffer = logger->activeBuffer % 3;			//change active buffer
	}
	if(logger->dataDump_Flag == 0xff){
		alt_u8 buffer[512];
		alt_u32 i;

		if(!logger->bufSaved){
			alt_printf("No data to dump\n\r");
		}
		for(i=0;i<logger->bufSaved;i++){
			sdCard_ReadData(SD_CARD_LOGGER_START_ADDRESS + i*512, 1, buffer);	//funkcja przesyla odczytane dane do PC
		}
		logger->dataDump_Flag = 0x00;
	}
	if(logger->freqChange_Flag == 0xff){
		//TODO: Zmien czestotliwosc probkowania
		logger->freqChange_Flag = 0x00;
	}
}

void dataLogger_init(DataLogger *logger){
	logger->bufIndex = 0;
	logger->activeBuffer = 1;
	logger->dataAcquire_Flag = 0;
	logger->dataDump_Flag = 0;
	logger->dataSaveToSD_Flag = 0;
	logger->freqChange_Flag = 0;
	logger->dataDestinationAddr = SD_CARD_LOGGER_START_ADDRESS;
	logger->bufSaved = 0;
}
