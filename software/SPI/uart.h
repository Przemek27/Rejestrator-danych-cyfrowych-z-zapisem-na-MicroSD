/*
 * uart.h
 *
 *  Created on: 31 sie 2017
 *      Author: Przemek
 */

#ifndef UART_H_
#define UART_H_

#include "alt_types.h"

/*
 * @param acquireData - flag set by specific command
 *
 * Function manage received commands*/
void uart_commandManage(alt_u8 *acquireData);

#endif /* UART_H_ */
