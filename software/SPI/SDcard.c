/*
 * SDcard.c
 *
 *  Created on: 25 maj 2017
 *      Author: Przemek
 */


#include "SDcard.h"
#include "SPI.h"
#include "system.h"
#include "sys/alt_stdio.h"
#include "altera_avalon_spi.h"


alt_u8 sdCard_Init(void){
	alt_u8 i;
	alt_u32 response[MAX_RESPONSE_LENGTH] = {0};

	alt_u8 cmd0[6] = {64,0,0,0,0,149};			//start condition = 01 + cmd_nr = 0; argument = 0,0,0,0; crc = 1001010 + stop condition = 1
	alt_u8 cmd8[6] = {72,0,0,1,170,135};
	alt_u8 cmd55[6] = {119,0,0,0,0,102};
	alt_u8 cmd58[6] = {122,0,0,0,0,117};
	alt_u8 acmd41[6] = {105,64,0,0,0,1};

	alt_u32 cmd0_response = 1;
	alt_u8 cmd8_response[5] = {1,0,0,1,170};
	alt_u8 cmd55_response = 1;
	alt_u8 acmd41_response = 0;

	/*Discard previous data*/
	if(spi_IsData(SPI_0_BASE)){
		spi_ReadData(SPI_0_BASE);
	}

	/*1) Apply more than 74 cycles of Dummy-clock to the SD card.*/
	for(i=0;i<10;i++){
		spi_SendByte(SPI_0_BASE, 0, 255);
		/*Discard response*/
		if(spi_IsData(SPI_0_BASE)){
			spi_ReadData(SPI_0_BASE);
		}
	}

	/*2) Select operation mode (SD mode or SPI mode)
	 In case of SPI mode operation, host should drive 1 pin (CD/DAT3) of SD Card I/F to �Low� level. Then, issue CMD0.
	 In case of SD mode operation, host should drive or detect 1 pin of SD Card I/F (Pull up register of 1 pin is pull
	up to �High� normally).
	 Card maintain selected operation mode except re-issue of CMD0 or power on below is SD mode initialization procedure.*/

	/*Send CMD0*/
	sdCard_SendCommand(cmd0, response, 1);
	/*Check response*/
	if(response[0] != cmd0_response){
		//Error
		return 0;
	}

	/*3) SEND_IF_COND (CMD8) is used to verify SD Memory Card interface operating condition*/

	/*Send CMD8*/
	sdCard_SendCommand(cmd8, response, 5);
	/*Check response*/
	for(i=0;i<5;i++){
		if(response[i] != cmd8_response[i]){
			//Error
			return 0;
		}
	}

	/*4) SD_SEND_OP_COND (ACMD41) is used to start initialization and to check if the card has completed initialization.*/

	do{									//Repeat until valid response
		/*CMD55 defines to the card that the next command is an application specific command rather than a standard command*/
		sdCard_SendCommand(cmd55, response, 1);
		/*Check response*/
		if(response[0] != cmd55_response){
			//Error
			return 0;
		}
		/*Send ACMD41*/
		sdCard_SendCommand(acmd41, response, 1);
	} while(response[0] == 1);

	/*Check response*/
	if(response[0] != acmd41_response){
		//Error
		return 0;
	}

	/*5) After initialization is completed, the host should get CCS information in the response of CMD58. CCS is
	valid when the card accepted CMD8 and after the completion of initialization. CCS=0 means that the card
	is SDSD. CCS=1 means that the card is SDHC or SDXC.*/

	/*CMD58 reads OCR register*/
	sdCard_SendCommand(cmd58, response, 5);

	return 1;
}

void delay(void){
	alt_u32 i;

	for(i=0;i<100000;i++){
		//do nothing
	}
}

void sdCard_SendCommand(alt_u8 *command,  alt_u32 *response, alt_u8 response_length){
	alt_u8 i;

	/*Send command*/
	for(i=0;i<6;i++){
		spi_SendByte(SPI_0_BASE, 0, command[i]);
		/*Discard response*/
		if(spi_IsData(SPI_0_BASE)){
			spi_ReadData(SPI_0_BASE);
		}
	}
	/*Read response*/
	for(i=0;i<(response_length+1);i++){
		spi_SendByte(SPI_0_BASE, 0, 255);
		/*Read response*/
		if(spi_IsData(SPI_0_BASE)){
			alt_u32 temp;

			temp = spi_ReadData(SPI_0_BASE);
			if(i>0){							//Ignore first response
				response[i-1] = temp;
				alt_printf("Response from microSD card: %x\n", response[i-1]);
			}
		}
	}
}