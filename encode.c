#include "encode.h"

void bgf_encode_trame(bgf_frame_t* tr, uint8_t id_message, uint8_t message) {
    uint16_t bgf_frame;
    bgf_frame = id_message;
    bgf_frame = (bgf_frame << 8) | message;
	set_bgf_frame_t(tr, bgf_frame);
}

void bcgv_to_mux(bcgv_frame_t* bcgv_frame ,dashboard_light_t dashboard_light, speed_t speed, kilometer_t kilometer, fuel_t fuel, rpm_t rpm) {

    set_kilometer_in_bcgv_frame_t(bcgv_frame, kilometer);
    set_rpm_in_bcgv_frame_t(bcgv_frame, rpm/10);
    set_speed_in_bcgv_frame_t(bcgv_frame, speed);
	set_fuel_percent_level_in_bcgv_frame_t(bcgv_frame, (fuel * MAX_FUEL_PERCENT) / MAX_FUEL);
	set_dashboard_light_in_bcgv_frame_t(bcgv_frame, dashboard_light);
}
