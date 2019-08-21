/*=============================================================================
 * Copyright (c) 2019, Sebastian Ceola <sebastian.ceola@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Version: 0.0.1
 *===========================================================================*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif


#define CONFIG_DEFAULT_SAMPLE_PERIOD    0


typedef struct _config_data
{
    unsigned    sample_period;
}
config_data;


int config_init( const char* filename, config_data* cfg );
int config_write( const char* filename, const config_data* cfg );

#ifdef __cplusplus
}
#endif
#endif
