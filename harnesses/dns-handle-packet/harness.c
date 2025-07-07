#include "FreeRTOS_IP.h"
#include "FreeRTOS_DNS_Parser.h"
#include <stdio.h>

int mayhem_process_input(char *buf, size_t len) {
    if (len < sizeof(DNSMessage_t)) {
        printf("dropping a short package\n");
        return -1;
    }
    NetworkBufferDescriptor_t net = {};
    net.pucEthernetBuffer = buf;
    net.xDataLength = len;
    uint32_t addr = ulDNSHandlePacket(&net);
    printf("parsed dns reply, the address is: %d\n", addr);
}
