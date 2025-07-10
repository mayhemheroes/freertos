#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "NetworkBufferManagement.h"
#include "mayhem.h"

#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <unistd.h>

int mayhem_process_input(char *buf, size_t len) {
    xNetworkBuffersInitialise();
    NetworkBufferDescriptor_t *net = pxGetNetworkBufferWithDescriptor(len, 0);
    net->pxInterface = create_mayhem_interface();
    net->pxEndPoint = net->pxInterface->pxEndPoint;
    memcpy(net->pucEthernetBuffer, buf, len);
    net->xDataLength = len;

    if (FreeRTOS_IPInit_Multi() == pdFALSE) {
        errx(1, "failed to initialize network stack");
    }
    IPStackEvent_t ev = { eNetworkRxEvent, NULL };
    ev.pvData = (void *) net;

    if (xQueueSendToBack(xNetworkEventQueue, &ev, pdMS_TO_TICKS(250)) == pdFALSE) {
        errx(1, "failed to send event to ip stack");
    }
    printf("succesfully sent data up the network stack\n");
    printf("starting the scheduler\n");
    vTaskStartScheduler();
    vTaskEndScheduler();
    return 0;
}
