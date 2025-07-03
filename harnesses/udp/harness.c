#include "FreeRTOS_IP.h"
#include "FreeRTOS_UDP_IP.h"
#include <stdio.h>

int mayhem_process_input(char *buf, size_t len) {
    if (len < sizeof(UDPPacket_t)) {
        printf("ignoring short packet\n");
        return -1;
    }
    NetworkBufferDescriptor_t net = {};
    BaseType_t wait_arp;
    net.pucEthernetBuffer = buf;
    net.xDataLength = len;
    int r = xProcessReceivedUDPPacket(&net, 4242, &wait_arp);
    printf("processed %d-long packet as a udp packet: %d\n", len, r);
}
