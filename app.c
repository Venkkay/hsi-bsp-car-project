#include "drv_api.h"
#include "fifo.h"
#include <errno.h>
#include <string.h>
//#include <data_management.h>

int main() {
    int32_t drv_fd, drv_frame;
    uint8_t udp_frame[DRV_UDP_100MS_FRAME_SIZE];

    drv_fd = drv_open();
    if (drv_fd == -1) {
        printf("Open connection with driver failed : %s...\n", strerror(errno));
        return DRV_ERROR;
    } else if (drv_fd == -2) {
        printf("Version of API is not compatible with driver : %s...\n", strerror(errno));
        return DRV_VER_MISMATCH;
    }

    printf("Lectures des trames UDP...\n");

    while (1) {
        drv_frame = drv_read_udp_100ms(drv_fd, udp_frame);
        if (drv_frame != 0) {
            printf("UDP frame read failed : %s...\n", strerror(errno));
            break;
        }

        printf("Trame UDP reçue : ");
        for (size_t i = 0; i < DRV_UDP_100MS_FRAME_SIZE; i++) {
            printf("%02X ", udp_frame[i]);
        }
        printf("\n");

    }

    drv_close(drv_fd);

    return EXIT_SUCCESS;
}