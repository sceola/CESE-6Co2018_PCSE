/*=============================================================================
 * Copyright (c) 2019, Sebastian Ceola <sebastian.ceola@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Version: 0.0.1
 *===========================================================================*/

#ifndef __MESSAGES_H__
#define __MESSAGES_H__


#define MESSAGES_QUEUE_SIZE 64
#define MESSAGES_QUEUE_NMBR 16


void messages_init( void );
void messages_print( const char* msg );


#ifdef __cplusplus
extern "C" {
#endif
#endif
