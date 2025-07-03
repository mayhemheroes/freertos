#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "FreeRTOS.h"

BaseType_t xApplicationGetRandomNumber( uint32_t * pulNumber )
{
    *pulNumber = 1337;
    return pdTRUE;
}


uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort )
{
    uint32_t pulNumber = 0;
    xApplicationGetRandomNumber( &pulNumber );
    return pulNumber;
}

/*  CALLED BY FREERTOS when conducting a DNS query
 *  Function that returns pdTRUE if the pcName matches the LLMNR node name */
BaseType_t xApplicationDNSQueryHook( const char * pcName )
{
    return pdTRUE;
}

BaseType_t xApplicationDNSQueryHook_Multi( struct xNetworkEndPoint * pxEndPoint,
                                           const char * pcName ) {
    return pdTRUE;
}

const char *pcApplicationHostnameHook( void ) {
    return "localhost";
}

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    configSTACK_DEPTH_TYPE * puxIdleTaskStackSize )
{
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    *ppxIdleTaskTCBBuffer = &( xIdleTaskTCB );
    *ppxIdleTaskStackBuffer = &( uxIdleTaskStack[ 0 ] );
    *puxIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vTaskDelay(const TickType_t xTicksToDelay) {}

void vAssertCalled(const char *filename, int linenum) {
    printf("Assertion failed at %s:%d\n", filename, linenum);
    exit(1);
}
