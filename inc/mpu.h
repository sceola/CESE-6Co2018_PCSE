/*=============================================================================
 * Copyright (c) 2019, Sebastian Ceola <sebastian.ceola@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Version: 0.0.1
 *===========================================================================*/

#ifndef __MPY_H__
#define __MPY_H__

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


int  mpu_init( void );
void mpu_get_accelerometer( float accel[3] );


#ifdef __cplusplus
}
#endif
#endif
