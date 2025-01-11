#ifndef DECODE_C_H
#define DECODE_C_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "drv_api.h"
#include "libs/data_lib/data_management.h"


void decode_mux_frame(mux_frame_t* mux_frame, uint8_t udpFrame[DRV_UDP_100MS_FRAME_SIZE]);
void decode_comodo_frame(serial_frame_t serial_frame[DRV_MAX_FRAMES], uint32_t data_len, comodo_frame_t comodo_frame[DRV_MAX_FRAMES]);

uint8_t check_crc8(uint8_t *data, size_t length, uint8_t polynomial, uint8_t initial_value);
dashboard_light_t decode_lights(mux_frame_t* mux_frame);

#endif //DECODE_C_H
