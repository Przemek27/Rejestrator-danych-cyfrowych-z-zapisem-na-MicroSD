/*
 * uart.c
 *
 *  Created on: 31 sie 2017
 *      Author: Przemek
 */


#include "uart.h"
#include "altera_avalon_uart_regs.h"
#include "sys/alt_stdio.h"

void uart_commandManage(DataLogger *logger){
	char c;

	c = alt_getchar();			//FIXME: funkcja czeka na uzytkownika

	switch(c){
		case 's': case 'S':
			alt_printf("start\n\r");
			logger->dataAcquire = 0xff;
			break;

		case 'p': case 'P':
			alt_printf("stop\n\r");
			logger->dataAcquire = 0x00;
			break;

		case 'd': case 'D':				//FIXME: komenda powinna byc aktywna jedynie po udanej akwizycji danych
			alt_printf("dump\n\r");
			logger->dataDump = 0xff;
			break;

		case 'f': case 'F':
			alt_printf("freq\n\r");
			logger->freqChange = 0xff;
			break;

		case '?':
			alt_printf("Commands:\n\r");
			alt_printf("'s' - Start data acquisition\n\r");
			alt_printf("'p' - Stop data acquisition\n\r");
			alt_printf("'d' - Read data\n\r");
			alt_printf("'f' - Change sample rate\n\r");
			break;

		default:
			alt_printf("Unknown command\n\rTo see all commands press '?'\n\r");
			break;
	}

}
