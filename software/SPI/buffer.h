/*
 * buffer.h
 *
 *  Created on: 21 wrz 2017
 *      Author: Przemek
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "alt_types.h"

typedef struct{
	alt_u8 data[512];
	alt_u32 index;
} Buffer;


#endif /* BUFFER_H_ */
