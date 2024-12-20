#include "drv_api.h"
#include "fifo.h"
#include <errno.h>
#include <string.h>
#include "libs/data_lib/data_management.h"

#include "decode.h"

int main() {
    int32_t drv_fd, drv_frame;
    uint8_t udp_frame[DRV_UDP_100MS_FRAME_SIZE];
    mux_frame_t mux_frame;

    serial_frame_t serial_frame[DRV_MAX_FRAMES];
    uint32_t data_len = 0;
    comodo_frame_t comodo_frame[DRV_MAX_FRAMES];

    drv_fd = drv_open();
    if (drv_fd == DRV_ERROR) {
        printf("Open connection with driver failed : %s...\n", strerror(errno));
        return DRV_ERROR;
    } else if (drv_fd == DRV_VER_MISMATCH) {
        printf("Version of API is not compatible with driver : %s...\n", strerror(errno));
        return DRV_VER_MISMATCH;
    }

    printf("Reading UDP frame and Serial frame...\n");

    while (1) {
        drv_frame = drv_read_udp_100ms(drv_fd, udp_frame);
        if (drv_frame != DRV_SUCCESS) {
            printf("UDP frame read failed : %s...\n", strerror(errno));
            break;
        }

        mux_frame = decode_mux_frame(udp_frame);
        /*printf("\n================\n");
        printf("Mux number:%d\n", mux_frame.frame_number);
        printf("Mux kilometer:%d\n", mux_frame.kilometer);
        printf("Mux speed:%d\n", mux_frame.speed);
        printf("Mux chassis issue:%d\n", mux_frame.chassis_issue);
        printf("Mux engine issue:%d\n", mux_frame.engine_issue);
        printf("Mux battery issue:%d\n", mux_frame.battery_issue);
        printf("Mux fuel level:%d\n", mux_frame.fuel_level);
        printf("Mux rpm:%d\n", mux_frame.rpm);
        printf("Mux CRC8:%d\n", mux_frame.crc8);
        printf("================\n");*/

        /*for (size_t i = 0; i < DRV_UDP_100MS_FRAME_SIZE; i++) {
            printf("%02X ", udp_frame[i]);
        }
        printf("\n");
         */

        drv_frame = drv_read_ser(drv_fd, serial_frame, &data_len);
        if (drv_frame != DRV_SUCCESS) {
            printf("Serial frame read failed : %s...\n", strerror(errno));
            break;
        }
        // The result is in comodo_frame.
        // You need to data_len to retreive the data from the table.
        decode_comodo_frame(serial_frame, data_len, comodo_frame);
    }

    drv_close(drv_fd);

    return EXIT_SUCCESS;
}