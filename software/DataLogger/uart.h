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

/*
 * @param logger - structure contains data logger's status flags
 *
 * Function manage received commands*/
void uart_commandManage(DataLogger *logger);

#endif /* UART_H_ */
