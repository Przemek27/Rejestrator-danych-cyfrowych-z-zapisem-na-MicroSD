/*
 * uart.c
 *
 *  Created on: 31 sie 2017
 *      Author: Przemek
 */

//TODO: uart_writeData(uint8_t *str)

#include "uart.h"

//Transmitter and receiver buffer
static alt_u8 rx_buffer[RX_BUFFER_SIZE];
static alt_u8 tx_buffer[TX_BUFFER_SIZE];

static alt_u8 rx_head = 0;
static alt_u8 tx_head = 0;
static alt_u8 rx_tail = 0;
static alt_u8 tx_tail = 0;

void uart_commandManage(DataLogger *logger){
	alt_u8 c;

	if(uart_isData()){

		c = uart_getByte();

		switch(c){
			case 's': case 'S':
				alt_printf("start\n\r");
				logger->dataAcquire_Flag = 0xff;
				break;

			case 'p': case 'P':
				alt_printf("stop\n\r");
				logger->dataAcquire_Flag = 0x00;
				break;

			case 'd': case 'D':
				alt_printf("dump\n\r");
				logger->dataDump_Flag = 0xff;
				break;

			case 'f': case 'F':
				alt_printf("freq\n\r");
				logger->freqChange_Flag = 0xff;
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
}

bool uart_isData(void){
	if(rx_tail != rx_head){			//check if there is data to read
		return true;
	}

	return false;
}

void uart_isr(void* isr_context){
	alt_u16 status;
	alt_u8 data;

	status = IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);

	if(status & ALTERA_AVALON_UART_STATUS_RRDY_MSK){		//receiver ready interrupt
		data = IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
		rx_buffer[rx_head++] = data;

		if(rx_head >= RX_BUFFER_SIZE)
			rx_head = 0;

		IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, status & ~ALTERA_AVALON_UART_STATUS_RRDY_MSK);			//reset the IRQ flag
	}
	else if(status & ALTERA_AVALON_UART_STATUS_TRDY_MSK){		//transmitter ready interrupt
		if(IORD_ALTERA_AVALON_UART_CONTROL(UART_0_BASE) & ALTERA_AVALON_UART_CONTROL_TRDY_MSK){
			alt_u16 control;

			if(tx_tail != tx_head){				//check if there is anything to send
				IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE, tx_buffer[tx_tail++]);

				if(tx_tail >= TX_BUFFER_SIZE)
					tx_tail = 0;
			}
			else{							//disable IRQ if tx_buffer is empty
				control = IORD_ALTERA_AVALON_UART_CONTROL(UART_0_BASE);
				IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, control & ~ALTERA_AVALON_UART_CONTROL_TRDY_MSK);	//disable IRQ for transmitter
			}
		}
	}
	else{
		alt_printf("UART Error!\n\r");
		IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, status & ~ALTERA_AVALON_UART_STATUS_E_MSK);			//reset the IRQ flag
	}
}

void uart_putByte(alt_u8 data){
	alt_u16 control;

	tx_buffer[tx_head++] = data;

	if(tx_head >= TX_BUFFER_SIZE)
		tx_head = 0;

	control = IORD_ALTERA_AVALON_UART_CONTROL(UART_0_BASE);
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, control | ALTERA_AVALON_UART_CONTROL_TRDY_MSK);		//enable IRQ for transmitter
}

alt_u8 uart_getByte(void){
	alt_u8 data;

	data = rx_buffer[rx_tail++];

	if(rx_tail >= RX_BUFFER_SIZE)
		rx_tail = 0;

	return data;
}

void uart_init(void){
	alt_u32 ret;

	/*Discard previous data*/
	if(IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE) & ALTERA_AVALON_UART_STATUS_RRDY_MSK){
		IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
	}
	/*Reset status register*/
	IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, 0x00);

	//Register the uart irq to be serviced by uart_isr() function
	ret = alt_ic_isr_register(UART_0_IRQ_INTERRUPT_CONTROLLER_ID, UART_0_IRQ, uart_isr, NULL, 0x0);
	alt_printf("UART IRQ register return %x \n\r", ret);
	//enable the IRQ for receiver ready and exception, in the IP core control register
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK | ALTERA_AVALON_UART_CONTROL_E_MSK);	//IRQ for transmitter is enabled after putting data to tx_buffer
}

