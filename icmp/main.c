/* Include standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>


#include "FreeRTOS_ICMP.h"

#include "FreeRTOSIPConfig.h"
#include <err.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        errx(1, "provide a file");
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        err(1, "open");
    }
    printf("The BUFSIZ=%d\n", BUFSIZ);
    NetworkBufferDescriptor_t net = {};
    uint8_t buf[BUFSIZ];
    net.pucEthernetBuffer = buf;
    ssize_t len = read(fd, buf, sizeof(buf));
    close(fd);
    printf("read %d bytes\n", len);
    if (len <= sizeof( ICMPPacket_t )) {
        printf("the packet is too small\n");
        return 1;
    }
    net.xDataLength = len;
    eFrameProcessingResult_t r = ProcessICMPPacket(&net);
    printf("processed ICMP packet with the following outcome: %d\n", r);
}
