/* Include standard libraries */
#include <stdio.h>
#include "FreeRTOS_ICMP.h"

int mayhem_process_input(char *buf, size_t len) {
    if (len < sizeof(ICMPPacket_t)) {
        printf("the packet is too small\n");
        return 1;
    }
    IPPacket_t *ip = ( IPPacket_t * )buf;

    if (ip->xEthernetHeader.usFrameType != ipIPv4_FRAME_TYPE &&
        ip->xEthernetHeader.usFrameType != ipIPv6_FRAME_TYPE) {
        printf("discarding non-ip packet");
        return 1;
    }

    NetworkBufferDescriptor_t net = {};
    net.pucEthernetBuffer = buf;
    net.xDataLength = len;
    eFrameProcessingResult_t r = ProcessICMPPacket(&net);
    printf("processed ICMP packet with the following outcome: %d\n", r);
}
