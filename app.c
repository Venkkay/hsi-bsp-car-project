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

    uint8_t frame_number = 1;

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
        if (frame_number > MAX_MUX_FRAME_NUMBER) {
            frame_number = 1;
        }
        // check frame number (if ok => decode ; if not log in error and continue for the next number)
        if (frame_number != udp_frame[0]) {
            frame_number = udp_frame[0];
            frame_number = frame_number + 1;
            printf("ERROR : UDP frame number wrong.\n");
        }else {
            frame_number = udp_frame[0];
            frame_number = frame_number + 1;
        }

        decode_mux_frame(&mux_frame, udp_frame);

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