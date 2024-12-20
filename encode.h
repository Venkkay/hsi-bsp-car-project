#ifndef ENCODE_H
#define ENCODE_H

#include "drv_api.h"
#include "libs/data_lib/data_management.h"

void bgf_encode_trame(bgf_frame_t* tr, uint8_t id_message, uint8_t message);
void bcgv_to_mux(bcgv_frame_t* bcgv_frame ,dashboard_light_t dashboard_light, speed_t speed, kilometer_t kilometer, fuel_t fuel, rpm_t rpm);

void create_bcgv_to_mux_frame(bcgv_frame_t* bcgv_frame, uint8_t udpFrame[DRV_UDP_200MS_FRAME_SIZE]);

#endif //ENCODE_H
