/*=============================================================================
 * Copyright (c) 2019, Sebastian Ceola <sebastian.ceola@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Version: 0.0.1
 *===========================================================================*/

#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


int  bluetooth_init( void );
void bluetooth_write( uint8_t data );
bool bluetooth_read( uint8_t* data );

#ifdef __cplusplus
}
#endif
#endif
