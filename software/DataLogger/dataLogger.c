/*
 * dataLogger.c
 *
 *  Created on: 25 wrz 2017
 *      Author: Przemek
 */

#include "dataLogger.h"

void dataLogger_manage(DataLogger *logger){
	//TODO:
	if(logger->dataSaveToSD == 0xff){
		//sdCard_SaveData(logger->buffer, address)
		logger->dataSaveToSD = 0x00;
	}
	if(logger->dataDump == 0xff){
		//Wyslij dane do PC
		logger->dataDump = 0x00;
	}
	if(logger->freqChange == 0xff){
		//Zmien czestotliwosc probkowania
		logger->freqChange = 0x00;
	}
}

void dataLogger_init(DataLogger *logger){
	logger->bufIndex = 0;
	logger->activeBuffer = 1;
	logger->dataAcquire = 0;
	logger->dataDump = 0;
	logger->dataSaveToSD = 0;
	logger->freqChange = 0;
}
