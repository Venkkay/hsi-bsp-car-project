#include "drv_api.h"
#include "fifo.h"
#include <errno.h>
#include <string.h>
#include "libs/data_lib/data_management.h"

#include "decode.h"
#include "encode.h"

int main() {
    int32_t drv_frame;
    uint8_t udp_frame[DRV_UDP_100MS_FRAME_SIZE];
    mux_frame_t mux_frame;

    serial_frame_t serial_frame[DRV_MAX_FRAMES];
    uint32_t data_len = 0;
    comodo_frame_t comodo_frame[DRV_MAX_FRAMES];

    bcgv_frame_t bcgv_frame;
    uint8_t udp_frame_bcgv[DRV_UDP_200MS_FRAME_SIZE];

    int32_t drv_fd = drv_open();
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

        decode_mux_frame(&mux_frame, udp_frame);
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
        // You need to data_len to retrieve the data from the table.
        decode_comodo_frame(serial_frame, data_len, comodo_frame);

        bcgv_to_mux(&bcgv_frame, 0, get_speed_from_mux_frame_t(mux_frame), get_kilometer_from_mux_frame_t(mux_frame), get_fuel_level_from_mux_frame_t(mux_frame), get_rpm_from_mux_frame_t(mux_frame));
        create_bcgv_to_mux_frame(&bcgv_frame, udp_frame_bcgv);
        drv_frame = drv_write_udp_200ms(drv_fd, udp_frame_bcgv);
        if (drv_frame != DRV_SUCCESS) {
            printf("UDP frame write failed : %s...\n", strerror(errno));
            break;
        }
    }

    drv_close(drv_fd);

    return EXIT_SUCCESS;
}