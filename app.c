/**
 * \file app.c
 * \brief Main application
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
*/

#include "drv_api.h"
#include "fifo.h"
#include <errno.h>
#include <string.h>

#include <time.h>

#include "libs/data_lib/data_management.h"
#include "decode.h"
#include "encode.h"
#include "fsm_classic_car_lights.h"
#include "fsm_indicator_light_warning.h"
#include "fsm_wipers_washer.h"


int main() {

    /* ==== Start of Initialization ====*/
    int32_t drv_frame;
    uint8_t udp_frame[DRV_UDP_100MS_FRAME_SIZE];
    mux_frame_t mux_frame;

    serial_frame_t serial_frame[DRV_MAX_FRAMES];
    serial_frame_t serial_frame_bgf[DRV_MAX_FRAMES];
    uint32_t data_len = 0;

    comodo_frame_t comodo_frame[DRV_MAX_FRAMES];
    bgf_frame_t bgf_frame_recv[DRV_MAX_FRAMES] = {};
    bgf_frame_t bgf_frame_send[5] = {};

    bcgv_frame_t bcgv_frame;
    uint8_t udp_frame_bcgv[DRV_UDP_200MS_FRAME_SIZE];

    uint8_t frame_number = 1;
    light_state_t current_position_light_state = ST_LIGHT_OFF;
    light_state_t new_position_light_state = current_position_light_state;

    light_state_t current_low_beam_state = ST_LIGHT_OFF;
    light_state_t current_high_beam_state = ST_LIGHT_OFF;

    indicator_state_t current_right_indicator_state = ST_INDICATOR_OFF;
    indicator_state_t current_left_indicator_state = ST_INDICATOR_OFF;
    indicator_state_t current_warning_state = ST_INDICATOR_OFF;

    wipers_washer_state_t current_wipers_washer_state = ST_WP_WS_ALL_OFF;

    dashboard_light_t dashboard_light;

    uint8_t position_light_state_timer = 0;
    uint8_t low_beam_state_timer = 0;
    uint8_t high_beam_state_timer = 0;

    uint8_t left_indicator_state_timer = 0;
    uint8_t right_indicator_state_timer = 0;
    uint8_t warning_state_timer = 0;

    uint8_t wipers_state_timer = 0;

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
        decode_bgf_frame(serial_frame, data_len, bgf_frame_recv);
        /* ==== End of Decoding Serial frame ====*/


        /* ==== Start of Algorithms ====*/

        for (size_t k = 0; k < data_len; k++) {
            for (size_t l = 0; l < 5; l++) {
                if ((bgf_frame_recv[k] & 0xFF00) == (bgf_frame_send[l] & 0xFF00)) {
                    if ((bgf_frame_recv[k] & 0x00FF) == (bgf_frame_send[l] & 0x00FF)) {
                        switch (bgf_frame_recv[k] & 0xFF00) {
                            case 0x01:
                                current_position_light_state = ST_LIGHT_ACQUITTED;
                                break;
                            case 0x02:
                                current_low_beam_state = ST_LIGHT_ACQUITTED;
                                break;
                            case 0x03:
                                current_high_beam_state = ST_LIGHT_ACQUITTED;
                                break;
                            case 0x04:
                                if ((bgf_frame_send[l] & 0x00FF) == 0) {
                                    current_right_indicator_state = ST_INDICATOR_ACQUITTED_OFF;
                                }else {
                                    current_right_indicator_state = ST_INDICATOR_ACQUITTED_ON;
                                }
                                break;
                            case 0x05:
                                if ((bgf_frame_send[l] & 0x00FF) == 0) {
                                    current_left_indicator_state = ST_INDICATOR_ACQUITTED_OFF;
                                }else {
                                    current_left_indicator_state = ST_INDICATOR_ACQUITTED_ON;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }

        if (current_position_light_state == ST_LIGHT_ON && position_light_state_timer == 0) {
            position_light_state_timer = clock();
        }else {
            position_light_state_timer = 0;
        }
        if (low_beam_state_timer == ST_LIGHT_ON && low_beam_state_timer == 0) {
            low_beam_state_timer = clock();
        }else {
            low_beam_state_timer = 0;
        }
        if (high_beam_state_timer == ST_LIGHT_ON && high_beam_state_timer == 0) {
            high_beam_state_timer = clock();
        }else {
            high_beam_state_timer = 0;
        }

        if (left_indicator_state_timer == ST_INDICATOR_ACTIVATED_ON && left_indicator_state_timer == 0) {
            left_indicator_state_timer = clock();
        }else if (left_indicator_state_timer == ST_INDICATOR_ACQUITTED_ON && left_indicator_state_timer == 0) {
            left_indicator_state_timer = clock();
        }else if (left_indicator_state_timer == ST_INDICATOR_ACTIVATED_OFF && left_indicator_state_timer == 0) {
            left_indicator_state_timer = clock();
        }else if (left_indicator_state_timer == ST_INDICATOR_ACQUITTED_OFF && left_indicator_state_timer == 0) {
            left_indicator_state_timer = clock();
        }else {
            left_indicator_state_timer = 0;
        }

        if (right_indicator_state_timer == ST_INDICATOR_ACTIVATED_ON && right_indicator_state_timer == 0) {
            right_indicator_state_timer = clock();
        }else if (right_indicator_state_timer == ST_INDICATOR_ACQUITTED_ON && right_indicator_state_timer == 0) {
            right_indicator_state_timer = clock();
        }else if (right_indicator_state_timer == ST_INDICATOR_ACTIVATED_OFF && right_indicator_state_timer == 0) {
            right_indicator_state_timer = clock();
        }else if (right_indicator_state_timer == ST_INDICATOR_ACQUITTED_OFF && right_indicator_state_timer == 0) {
            right_indicator_state_timer = clock();
        }else {
            right_indicator_state_timer = 0;
        }

        if (warning_state_timer == ST_INDICATOR_ACTIVATED_ON && warning_state_timer == 0) {
            warning_state_timer = clock();
        }else if (warning_state_timer == ST_INDICATOR_ACQUITTED_ON && warning_state_timer == 0) {
            warning_state_timer = clock();
        }else if (warning_state_timer == ST_INDICATOR_ACTIVATED_OFF && warning_state_timer == 0) {
            warning_state_timer = clock();
        }else if (warning_state_timer == ST_INDICATOR_ACQUITTED_OFF && warning_state_timer == 0) {
            warning_state_timer = clock();
        }else {
            warning_state_timer = 0;
        }

        if (wipers_state_timer == ST_TMR_WP_WS_OFF && wipers_state_timer == 0) {
            wipers_state_timer = clock();
        }else {
            wipers_state_timer = 0;
        }


        for (size_t i = 0; i < data_len; i++) {
            //position_light_comodo(current_position_light_state, get_cmd_position_light_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            //low_beam_comodo(current_low_beam_state, get_cmd_position_light_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            //high_beam_comodo(current_high_beam_state, get_cmd_position_light_from_comodo_frame_t(comodo_frame[i]), /* timer */);

            //warning_comodo(current_warning_state, get_cmd_warning_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            // right_indicator_comodo(current_right_indicator_state, get_cmd_right_indicator_from_comodo_frame_t(comodo_frame[i]), /* timer */);
            //left_indicator_comodo(current_left_indicator_state, get_cmd_left_indicator_from_comodo_frame_t(comodo_frame[i]), /* timer */);

            wipers_washer_comodo(current_wipers_washer_state, get_cmd_wipers_from_comodo_frame_t(comodo_frame[i]), get_cmd_washer_from_comodo_frame_t(comodo_frame[i]), /* timer */);
        }

        // === Lights on the dashboard ===
        if (current_position_light_state == ST_LIGHT_ACQUITTED) {
            set_position_light_in_dashboard_light_t(&dashboard_light, 1);
        }else {
            set_position_light_in_dashboard_light_t(&dashboard_light, 0);
        }
        if (current_low_beam_state == ST_LIGHT_ACQUITTED) {
            set_low_beam_in_dashboard_light_t(&dashboard_light, 1);
        }else {
            set_low_beam_in_dashboard_light_t(&dashboard_light, 0);
        }
        if (current_high_beam_state == ST_LIGHT_ACQUITTED) {
            set_high_beam_in_dashboard_light_t(&dashboard_light, 1);
        }else {
            set_high_beam_in_dashboard_light_t(&dashboard_light, 0);
        }

        if (current_warning_state == ST_INDICATOR_ACQUITTED_ON) {
            set_warning_in_dashboard_light_t(&dashboard_light, 1);
        }else if (current_warning_state == ST_INDICATOR_ACQUITTED_OFF) {
            set_warning_in_dashboard_light_t(&dashboard_light, 0);
        }else {
            set_warning_in_dashboard_light_t(&dashboard_light, 0);
        }

        if (current_wipers_state == ST_WP_ON || current_wipers_state == ST_WP_WS_ON) {
            set_wiper_active_in_dashboard_light_t(&dashboard_light, 1);
        }else {
            set_wiper_active_in_dashboard_light_t(&dashboard_light, 0);
        }

        if (current_washer_state == ST_WP_WS_ON) {
            set_washer_active_in_dashboard_light_t(&dashboard_light, 1);
        }else {
            set_washer_active_in_dashboard_light_t(&dashboard_light, 0);
        }

        /* ==== End of Algorithms ====*/

        /* ==== Start of Encoding and Writing to UDP ====*/
        bcgv_to_mux(&bcgv_frame, dashboard_light, get_speed_from_mux_frame_t(mux_frame), get_kilometer_from_mux_frame_t(mux_frame), get_fuel_level_from_mux_frame_t(mux_frame), get_rpm_from_mux_frame_t(mux_frame));
        create_bcgv_to_mux_frame(&bcgv_frame, udp_frame_bcgv);

        drv_frame = drv_write_udp_200ms(drv_fd, udp_frame_bcgv);
        if (drv_frame != DRV_SUCCESS) {
            printf("UDP frame write failed : %s...\n", strerror(errno));
            break;
        }
        /* ==== End of Encoding and Writing to UDP ====*/

        /* ==== Start of Encoding and Writing to Serial ====*/

        if (current_position_light_state == ST_LIGHT_ON) {
            bgf_encode_frame(&bgf_frame_send[0], BGF_POSITION, 1);
        }else if (current_position_light_state == ST_LIGHT_OFF) {
            bgf_encode_frame(&bgf_frame_send[0], BGF_POSITION, 0);
        }
        if (current_low_beam_state == ST_LIGHT_ON) {
            bgf_encode_frame(&bgf_frame_send[1], BGF_LOW_BEAM, 1);
        }else if (current_low_beam_state == ST_LIGHT_OFF) {
            bgf_encode_frame(&bgf_frame_send[1], BGF_LOW_BEAM, 0);
        }
        if (current_high_beam_state == ST_LIGHT_ON) {
            bgf_encode_frame(&bgf_frame_send[2], BGF_HIGH_BEAM, 1);
        }else if (current_high_beam_state == ST_LIGHT_OFF) {
            bgf_encode_frame(&bgf_frame_send[2], BGF_HIGH_BEAM, 0);
        }
        if (current_right_indicator_state == ST_INDICATOR_ACQUITTED_ON) {
            bgf_encode_frame(&bgf_frame_send[3], BGF_RIGHT_INDICATOR, 1);
        } else if (current_right_indicator_state == ST_INDICATOR_ACQUITTED_OFF) {
            bgf_encode_frame(&bgf_frame_send[3], BGF_RIGHT_INDICATOR, 0);
        } else if (current_right_indicator_state == ST_INDICATOR_OFF) {
            bgf_encode_frame(&bgf_frame_send[3], BGF_RIGHT_INDICATOR, 0);
        }
        if (current_left_indicator_state == ST_INDICATOR_ACQUITTED_ON) {
            bgf_encode_frame(&bgf_frame_send[4], BGF_LEFT_INDICATOR, 1);
        } else if (current_left_indicator_state == ST_INDICATOR_ACQUITTED_OFF) {
            bgf_encode_frame(&bgf_frame_send[4], BGF_LEFT_INDICATOR, 0);
        } else if (current_left_indicator_state == ST_INDICATOR_OFF) {
            bgf_encode_frame(&bgf_frame_send[4], BGF_LEFT_INDICATOR, 0);
        }

        encode_serial_frame_bgf(serial_frame_bgf, bgf_frame_send, sizeof(bgf_frame_send));

        drv_frame = drv_write_ser(drv_fd, serial_frame_bgf, sizeof(bgf_frame_send));
        if (drv_frame != DRV_SUCCESS) {
            printf("Serial frame write failed : %s...\n", strerror(errno));
            break;
        }
        /* ==== End of Encoding and Writing to Serial ====*/
    }

    drv_close(drv_fd);

    return EXIT_SUCCESS;
}