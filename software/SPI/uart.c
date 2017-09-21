/*
 * uart.c
 *
 *  Created on: 31 sie 2017
 *      Author: Przemek
 */

//TODO: uart_manage() - funkcja dzialaj¹ca w nieskoñczonej pêtli wykrywaj¹ca komendy

#include "uart.h"
#include "altera_avalon_uart_regs.h"

void uart_commandManage(alt_u8 *acquireData){
	char c;

	c = alt_getchar();

	switch(c){
		case 's': case 'S':
			alt_printf("start\n\r");
			*acquireData = 0xff;
			break;

		case 'p': case 'P':
			alt_printf("stop\n\r");
			*acquireData = 0x00;
			break;

		case 'd': case 'D':				//FIXME: komenda powinna byc aktywna jedynie po udanej akwizycji danych
			alt_printf("dump\n\r");
			//TODO: dump data to PC (or to microSD Card ??)
			break;

		case 'f': case 'F':
			alt_printf("freq\n\r");
			//TODO: change frequency
			break;
	}

}
