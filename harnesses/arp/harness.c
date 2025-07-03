#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_ARP.h"

int mayhem_process_input(char *buf, size_t len) {
    NetworkBufferDescriptor_t net = {};
    net.pucEthernetBuffer = buf;
    net.xDataLength = len;
    eFrameProcessingResult_t r = eARPProcessPacket(&net);
    printf("processed %d bytes as an arp packet, outcome %d\n", len, r);
}
