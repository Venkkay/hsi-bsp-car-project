#include "drv_api.h"
#include "fifo.h"
#include <errno.h>
#include <string.h>
#include "libs/data_lib/data_management.h"

#include "decode.h"
#include "encode.h"
#include "fsm_classic_car_lights.h"

int main() {
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
        } else {
            frame_number = udp_frame[0];
            frame_number = frame_number + 1;
        }

        decode_mux_frame(&mux_frame, udp_frame);
        decode_lights(&mux_frame);
        drv_frame = drv_read_ser(drv_fd, serial_frame, &data_len);
        if (drv_frame != DRV_SUCCESS) {
            printf("Serial frame read failed : %s...\n", strerror(errno));
            break;
        }
        // The result is in comodo_frame.
        // You need to data_len to retrieve the data from the table.
        decode_comodo_frame(serial_frame, data_len, comodo_frame);

        dashboard_light = decode_lights(&mux_frame);

        bcgv_to_mux(&bcgv_frame, dashboard_light, get_speed_from_mux_frame_t(mux_frame), get_kilometer_from_mux_frame_t(mux_frame), get_fuel_level_from_mux_frame_t(mux_frame), get_rpm_from_mux_frame_t(mux_frame));

        for (size_t i = 0; i < DRV_MAX_FRAMES; i++) { //être sûr qu'il y a une trame à traiter
            uint8_t position_light_value = get_cmd_position_light_from_comodo_frame_t(comodo_frame[i]);
            uint8_t low_beam_value = get_cmd_low_beam_from_comodo_frame_t(comodo_frame[i]);
            uint8_t high_beam_value = get_cmd_high_beam_from_comodo_frame_t(comodo_frame[i]);

            light_state_t new_position_light_state = fsm_classic_car_lights(current_position_light_state, position_light_value);
            light_state_t new_low_beam_state = fsm_classic_car_lights(current_low_beam_state, low_beam_value);
            light_state_t new_high_beam_value = fsm_classic_car_lights(current_high_beam_state, high_beam_value);

            uint8_t warning_value = get_cmd_warning_from_comodo_frame_t(comodo_frame[i]);
            uint8_t right_indicator_value = get_cmd_right_indicator_from_comodo_frame_t(comodo_frame[i]);
            uint8_t left_indicator_value = get_cmd_left_indicator_from_comodo_frame_t(comodo_frame[i]);

            light_state_t new_warning_state = fsm_flashing_lights_warnings(current_warning_state, warning_value);
            light_state_t new_right_indicator_state = fsm_flashing_lights_warnings(current_right_indicator_state, right_indicator_value);
            light_state_t new_left_indicator_value = fsm_flashing_lights_warnings(current_left_indicator_state, left_indicator_value);

            uint8_t wipers_value = get_cmd_wipers_from_comodo_frame_t(comodo_frame[i]);
            uint8_t washer_value = get_cmd_washer_from_comodo_frame_t(comodo_frame[i]);

            light_state_t new_wipers_state = fsm_wiper_and_washer(current_wipers_state, wipers_value);
            light_state_t new_washer_state = fsm_wiper_and_washer(current_washer_state, washer_value);
        }

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