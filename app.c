#include "drv_api.h"
#include "fifo.h"
#include <errno.h>
#include <string.h>

#include "libs/data_lib/data_management.h"
#include "decode.h"
#include "encode.h"
#include "fsm_classic_car_lights.h"
#include "fsm_indicator_light_warning.h"

int main() {

    /* ==== Start of Initialization ====*/
    int32_t drv_frame;
    uint8_t udp_frame[DRV_UDP_100MS_FRAME_SIZE];
    mux_frame_t mux_frame;

    serial_frame_t serial_frame[DRV_MAX_FRAMES];
    uint32_t data_len = 0;

    comodo_frame_t comodo_frame[DRV_MAX_FRAMES];
    bgf_frame_t bgf_frame[DRV_MAX_FRAMES];

    bcgv_frame_t bcgv_frame;
    uint8_t udp_frame_bcgv[DRV_UDP_200MS_FRAME_SIZE];

    uint8_t frame_number = 1;
    light_state_t current_position_light_state = ST_LIGHT_OFF;
    light_state_t current_low_beam_state = ST_LIGHT_OFF;
    light_state_t current_high_beam_state = ST_LIGHT_OFF;

    indicator_state_t current_right_indicator_state = ST_INDICATOR_OFF;
    indicator_state_t current_left_indicator_state = ST_INDICATOR_OFF;
    indicator_state_t current_warning_state = ST_INDICATOR_OFF;

    wipers_washer_state_t current_wipers_state = ST_WP_WS_ALL_OFF;
    wipers_washer_state_t current_washer_state = ST_WP_WS_ALL_OFF;

    dashboard_light_t dashboard_light;

    int32_t drv_fd = drv_open();
    if (drv_fd == DRV_ERROR) {
        printf("Open connection with driver failed : %s...\n", strerror(errno));
        return DRV_ERROR;
    } else if (drv_fd == DRV_VER_MISMATCH) {
        printf("Version of API is not compatible with driver : %s...\n", strerror(errno));
        return DRV_VER_MISMATCH;
    }

    printf("Reading UDP frame and Serial frame...\n");
    /* ==== End of Initialization ====*/

    while (1) {
        /* ==== Start of Reading UDP frame ====*/
        // read udp frame
        drv_frame = drv_read_udp_100ms(drv_fd, udp_frame);

        if (drv_frame != DRV_SUCCESS) {
            printf("UDP frame read failed : %s...\n", strerror(errno));
            break;
        }

        /* ==== End of Reading UDP frame ====*/
        /* ==== Start of Checking frame number====*/
        if (frame_number > MAX_MUX_FRAME_NUMBER) {
            frame_number = 1;
        }

        // check frame number (if ok => decode ; if not log in error and continue for the next number)
        if (frame_number != udp_frame[0]) {
            frame_number = udp_frame[0];
            frame_number = frame_number + 1;
            printf("ERROR : UDP frame number wrong.\n");
        } else {
            frame_number = udp_frame[0];
            frame_number = frame_number + 1;
        }
        /* ==== End of Checking frame number====*/

        /* ==== Start of Decoding UDP frame ====*/
        decode_mux_frame(&mux_frame, udp_frame);
        dashboard_light = decode_lights(&mux_frame);
        /* ==== End of Decoding UDP frame ====*/

        /* ==== Start of Reading Serial frame ====*/
        drv_frame = drv_read_ser(drv_fd, serial_frame, &data_len);
        if (drv_frame != DRV_SUCCESS) {
            printf("Serial frame read failed : %s...\n", strerror(errno));
            break;
        }
        /* ==== End of Reading Serial frame ====*/

        /* ==== Start of Decoding Serial frame ====*/
        // The result is in comodo_frame.
        // You need to data_len to retrieve the data from the table.
        decode_comodo_frame(serial_frame, data_len, comodo_frame);
        decode_bgf_frame(serial_frame, data_len, bgf_frame);
        /* ==== End of Decoding Serial frame ====*/

        bcgv_to_mux(&bcgv_frame, dashboard_light, get_speed_from_mux_frame_t(mux_frame), get_kilometer_from_mux_frame_t(mux_frame), get_fuel_level_from_mux_frame_t(mux_frame), get_rpm_from_mux_frame_t(mux_frame));

        /* ==== Start of Algorithms ====*/

        for (size_t i = 0; i < data_len; i++) {
            position_light_comodo(current_position_light_state, get_cmd_position_light_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            low_beam_comodo(current_low_beam_state, get_cmd_position_light_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            high_beam_comodo(current_high_beam_state, get_cmd_position_light_from_comodo_frame_t(comodo_frame[i]), /* timer */);

            warning_comodo(current_warning_state, get_cmd_warning_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            right_indicator_comodo(current_right_indicator_state, get_cmd_right_indicator_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            left_indicator_comodo(current_left_indicator_state, get_cmd_left_indicator_from_comodo_frame_t(comodo_frame[i]), /* timer */);

            /* Need to be commit */
            //wipers_comodo(current_wipers_state, get_cmd_wipers_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            //washer_comodo(current_washer_state, get_cmd_washer_from_comodo_frame_t(comodo_frame[i]), /* timer */);
        }

        /* ==== End of Algorithms ====*/

        /* ==== Start of Encoding and Writing to UDP ====*/
        create_bcgv_to_mux_frame(&bcgv_frame, udp_frame_bcgv);

        drv_frame = drv_write_udp_200ms(drv_fd, udp_frame_bcgv);
        if (drv_frame != DRV_SUCCESS) {
            printf("UDP frame write failed : %s...\n", strerror(errno));
            break;
        }
        /* ==== End of Encoding and Writing to UDP ====*/

        /* ==== Start of Encoding and Writing to Serial ====*/
        /*encode_serial_frame_bgf(serial_frame_bgf, bgf_frame, data_len_bgf);

        drv_frame = drv_write_ser(drv_fd, serial_frame_bgf, data_len_bgf);
        if (drv_frame != DRV_SUCCESS) {
            printf("Serial frame write failed : %s...\n", strerror(errno));
            break;
        }/*
        /* ==== End of Encoding and Writing to Serial ====*/
    }

    drv_close(drv_fd);

    return EXIT_SUCCESS;
}