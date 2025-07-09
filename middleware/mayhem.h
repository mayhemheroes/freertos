#include "FreeRTOS_IP.h"

int init_network_buffer(NetworkBufferDescriptor_t *net, char *buf, size_t len);
void release_network_buffer(NetworkBufferDescriptor_t *net);
