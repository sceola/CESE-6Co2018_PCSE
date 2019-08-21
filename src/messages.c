#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <string.h>
#include <stdio.h>

#include "messages.h"


char          s__buffer[MESSAGES_QUEUE_SIZE];
QueueHandle_t s__queueMessages;

void vTaskMessages( void *pParam )
{
    while (1)
    {
        // Esta tarea se dispara siempre que haya un mensaje para enviar, pero
        // tiene baja prioridad para que no frene a ninguna mas importante.
        BaseType_t xSts = xQueueReceive(s__queueMessages, &s__buffer, portMAX_DELAY);
        if (xSts == pdPASS)
        {
            // En caso de que alguien mandara un mensaje que no entra en
            // MESSAGES_QUEUE_SIZE le pisamos el ultimo caracter al '\0'.
            s__buffer[MESSAGES_QUEUE_SIZE-1] = '\0';
            printf(s__buffer);
        }
    }
}

void messages_init( void )
{
    s__queueMessages = xQueueCreate(MESSAGES_QUEUE_NMBR, MESSAGES_QUEUE_SIZE);

    xTaskCreate( vTaskMessages,
                 (const char*) "Task Messages",
                 configMINIMAL_STACK_SIZE*2,
                 NULL,
                 tskIDLE_PRIORITY+4,
                 NULL );
}

void messages_print( const char* msg )
{
    xQueueSendToBack(s__queueMessages, msg, 0);
}
