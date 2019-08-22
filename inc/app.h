/*=============================================================================
 * Copyright (c) 2019, Sebastian Ceola <sebastian.ceola@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Version: 0.0.1
 *===========================================================================*/

#ifndef __APP_H__
#define __APP_H__

#include <FreeRTOS.h>
#include <semphr.h>
#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "buffer_queue.h"
#include "debouncing.h"

#ifdef __cplusplus
extern "C" {
#endif


/// Nombre del archivo de configuracion en la SD.
#define APP_SD_CONFIG_FILENAME  "config.bin"

/// Timeout de espera de respuesta por Bluetooth en ms.
#define APP_BLUETOOTH_TIMEOUT   250
/// Duracion del LED de error en caso de no tener respuesta por Bluetooth en ms.
#define APP_ERROR_ONTIME        500

/// Tiempo de actualizacion del acelerometro en ms.
#define APP_ACCEL_TASK_PERIOD   1000

/// Canal del ADC a muestrear.
#define APP_ADC_CHANNEL         ADC_CH2
/// Periodo minimo de muestreo (Ts = APP_ADC_MIN_RATE + 1).
#define APP_ADC_MIN_RATE         0
/// Periodo maximo de muestreo (Ts = APP_ADC_MIN_RATE + 1).
#define APP_ADC_MAX_RATE        10

#define APP_BUTTON_PIN_LEFT     BOARD_TEC_1  /// Tecla izquierda
#define APP_BUTTON_PIN_RIGHT    BOARD_TEC_4  /// Tecla derecha
#define APP_BUTTON_PIN_UP       BOARD_TEC_3  /// Tecla arriba
#define APP_BUTTON_PIN_DOWN     BOARD_TEC_2  /// Tecla abajo

/// Cuantas muestras del ADC almacenar antes de enviarlas todas por Bluetooth.
#define APP_DATA_BUF_SIZE       16
/**
 * Cuantos buffers se crearan para almacenar muestras del ADC.
 * Estos son los que se utilizaran con buffer_queue para intercambiar datos
 * entre la tarea del ADC y de APP.
 */
#define APP_DATA_BUF_NMBR        8


/**
 * Estructura que almacena la configuracion de toda la aplicacion.
 * Prestar atencion que hay cosas que se leen/escriben desde distintas tareas,
 * esta indicado con un comentario a cual pertenece cada cosa.
 */
typedef struct _app_type
{
    // Para la tarea de configuracion
    debouncer_type      button_left;
    debouncer_type      button_right;
    debouncer_type      button_up;
    debouncer_type      button_down;
    SemaphoreHandle_t   semaphore_config; // Para indicar que hay una configuracion nueva
    config_data         config;
    bool                config_sd_present;

    // Indicacion de error para LED
    SemaphoreHandle_t   semaphore_error;

    // Indicacion de espera de respuesta por Bluetooth
    SemaphoreHandle_t   semaphore_reply;

    // Para la tarea que envia datos por la Bluetooth
    float               accel[3];

    // Para la tarea del ADC
    buffer_queue        data_queue;
    unsigned            samples_in_buffer;
    uint8_t*            current_buffer;

    // FIFO para los nuevos valores leidos del MPU
    QueueHandle_t       queue_mpu;
}
app_type;


/**
 * Inicializa la aplicacion y crea todas las tareas:
 *   * ADC
 *   * APP
 *   * Bluetooth
 *   * Teclas
 *   * LED/Error
 */
void app_init( app_type* app );


#ifdef __cplusplus
}
#endif
#endif
