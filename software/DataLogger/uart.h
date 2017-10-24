/*
 * uart.h
 *
 *  Created on: 31 sie 2017
 *      Author: Przemek
 */

#ifndef UART_H_
#define UART_H_

#include "alt_types.h"
#include "dataLogger.h"
#include "stdbool.h"
#include "system.h"
#include "altera_avalon_uart_regs.h"
#include "sys/alt_stdio.h"
#include <stddef.h>
#include "sys/alt_irq.h"

#define TX_BUFFER_SIZE 256
#define RX_BUFFER_SIZE 256

/*
 * @param logger - structure contains data logger's status flags
 *
 * Function manage received commands*/
void uart_commandManage(DataLogger *logger);

/*
 * Check if in receiver buffer is data*/
bool uart_isData(void);

/*
 * ISR for UART*/
void uart_isr(void* isr_context);

/*
 * @param data - data stored in uart's transmiter buffer*/
void uart_putByte(alt_u8 data);

/*
 * @return data from uart's receiver buffer
 * !! Function should be used only if there is data in rx_buffer !!
 * [use uart_isData()]*/
alt_u8 uart_getByte(void);

/*
 * Function initializes UART*/
void uart_init(void);

#endif /* UART_H_ */
