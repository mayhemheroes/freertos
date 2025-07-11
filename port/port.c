/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#include "FreeRTOS.h"
#include "task.h"

TaskFunction_t main_task;
void *main_args;

BaseType_t xPortStartScheduler( void )
{
    return pdTRUE;
}

void vPortEndScheduler( void )
{
}

StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                     TaskFunction_t pxCode,
                                     void * pvParameters )
{
    printf("setting the main task to %p\n", pxCode);
    main_task = pxCode;
    main_args = pvParameters;
    return pxTopOfStack;
}

void vPortYield(void) {
    if (main_task) {
        printf("calling the main task\n");
        main_task(main_args);
        printf("it has returned");
        main_task = NULL;
    } else {
        printf("main task is not set\n");
        exit(0);
    }
}
