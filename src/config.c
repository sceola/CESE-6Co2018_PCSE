#include <sapi_spi.h>
#include <ff.h>
#include <fssdc.h>

#include "config.h"


static FATFS    s__fatfs;
static FIL      s__fp;


void s__write_config( FIL* fp, const config_data* cfg )
{
    UINT bw;
    FRESULT fr = f_write(&s__fp, &cfg->sample_period, 1, &bw);
    if (fr != FR_OK)
    {
        // ERROR
        printf("ERROR: f_write\n\r");
    }
    else
    {
        if (bw != 1)
        {
            // ERROR, no pudo escribir el byte
            printf("ERROR: f_write &bw\n\r");
        }
    }
}


int config_init( const char* filename, config_data* cfg )
{
    int ret = -1;

    // Inicializar SPI/SD
    spiConfig(SPI0);
    FSSDC_InitSPI();
    if (f_mount(&s__fatfs, "SDC:", 0) != FR_OK)
    {
        // ERROR
        printf("ERROR: f_mount\n\r");
    }
    else
    {
        // Primero intentamos crear un archivo de configuracion nuevo, esto es
        // para el caso en que la SD este vacia y no exista entonces lo creamos
        // con valores por defecto.
        FRESULT fr = f_open(&s__fp, filename, FA_CREATE_NEW | FA_WRITE);
        if (fr == FR_OK || fr == FR_EXIST)
        {
            if (fr == FR_OK)
            {
                // Config por defecto.
                config_data def_cfg;
                def_cfg.sample_period = CONFIG_DEFAULT_SAMPLE_PERIOD;

                s__write_config(&s__fp, &def_cfg);
                f_close(&s__fp);
            }

            fr = f_open(&s__fp, filename, FA_READ);
            if (fr == FR_OK)
            {
                UINT bw;
                fr = f_read(&s__fp, &cfg->sample_period, 1, &bw);
                if (fr != FR_OK)
                {
                    // ERROR
                    printf("ERROR: f_read\n\r");
                }
                else
                {
                    if (bw != 1)
                    {
                        // ERROR, no pudo leer el byte
                        printf("ERROR: f_read &bw\n\r");
                    }
                    else
                    {
                        // Recien aca indicamos que todo esta bien:
                        // Se creo el archivo nuevo si no existia y se escribio
                        // la config por defecto.
                        // Se leyo el archivo de configuracion.
                        printf("CONFIG: FS is UP\n\r");
                        ret = 0;
                    }
                }
                f_close(&s__fp);
            }
            else
            {
                // ERROR
                printf("ERROR: f_open 2\n\r");
            }
        }
        else
        {
            // ERROR
            printf("ERROR: f_open 1\n\r");
        }
    }
    return ret;
}

void config_write( const char* filename, const config_data* cfg )
{
    FRESULT fr = f_open(&s__fp, filename, FA_WRITE);
    if (fr == FR_OK)
    {
        s__write_config(&s__fp, cfg);
        f_close(&s__fp);
    }
    else
    {
        // ERROR
        printf("ERROR: config_write open\n\r");
    }
}
