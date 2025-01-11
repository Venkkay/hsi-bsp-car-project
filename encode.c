#include "encode.h"

void bgf_encode_frame(bgf_frame_t* fr, uint8_t id_message, uint8_t message) {
    uint16_t bgf_frame;
    bgf_frame = id_message;
    bgf_frame = (bgf_frame << 8) | message;
	set_bgf_frame_t(fr, bgf_frame);
}

void bcgv_to_mux(bcgv_frame_t* bcgv_frame ,dashboard_light_t dashboard_light, speed_t speed, kilometer_t kilometer, fuel_t fuel, rpm_t rpm) {

    set_kilometer_in_bcgv_frame_t(bcgv_frame, kilometer);
    set_rpm_in_bcgv_frame_t(bcgv_frame, rpm/10);
    set_speed_in_bcgv_frame_t(bcgv_frame, speed);
	set_fuel_percent_level_in_bcgv_frame_t(bcgv_frame, (fuel * MAX_FUEL_PERCENT) / MAX_FUEL);
	set_dashboard_light_in_bcgv_frame_t(bcgv_frame, dashboard_light);
}

void create_bcgv_to_mux_frame(bcgv_frame_t* bcgv_frame, uint8_t udpFrame[DRV_UDP_200MS_FRAME_SIZE]) {
	kilometer_t kilometer = get_kilometer_from_bcgv_frame_t(*bcgv_frame);
    speed_t speed = get_speed_from_bcgv_frame_t(*bcgv_frame);
    rpm_t rpm = get_rpm_from_bcgv_frame_t(*bcgv_frame);
    fuel_percent_t fuel = get_fuel_percent_level_from_bcgv_frame_t(*bcgv_frame);
    dashboard_light_t light = get_dashboard_light_from_bcgv_frame_t(*bcgv_frame);

    uint8_t lightdash1 = 0x00;
    uint8_t lightdash2 = 0x00;

    lightdash1 = (lightdash1) | get_position_light_from_dashboard_light_t(light);
	lightdash1 = (lightdash1 << 1) | get_low_beam_from_dashboard_light_t(light);
	lightdash1 = (lightdash1 << 1) | get_high_beam_from_dashboard_light_t(light);

    // fuel light
    if(fuel <= 5){
	  lightdash1 = (lightdash1 << 1) | 1;
    }else{
      lightdash1 = (lightdash1 << 1) | 0;
    }

	lightdash1 = (lightdash1 << 1) | get_motor_issue_from_dashboard_light_t(light);
	lightdash1 = (lightdash1 << 1) | get_pressure_issue_from_dashboard_light_t(light);
	lightdash1 = (lightdash1 << 1);
	lightdash1 = (lightdash1 << 1) | get_discharged_battery_from_dashboard_light_t(light);

    lightdash2 = (lightdash2) | get_warning_from_dashboard_light_t(light);
	lightdash2 = (lightdash2 << 1) | get_battery_issue_from_dashboard_light_t(light);
	lightdash2 = (lightdash2 << 1) | get_coolant_temperature_from_dashboard_light_t(light);
	lightdash2 = (lightdash2 << 1) | get_motor_pressure_from_dashboard_light_t(light);
	lightdash2 = (lightdash2 << 1) | get_oil_overheat_from_dashboard_light_t(light);
	lightdash2 = (lightdash2 << 1) | get_brake_issue_from_dashboard_light_t(light);
	lightdash2 = (lightdash2 << 1) | get_wiper_active_from_dashboard_light_t(light);
	lightdash2 = (lightdash2 << 1) | get_washer_active_from_dashboard_light_t(light);



	udpFrame[0] = lightdash1; // light 1
	udpFrame[1] = lightdash2; // light 2
	udpFrame[2] = kilometer & 0xFF000000; // kilometre 1
	udpFrame[3] = kilometer & 0x00FF0000; // kilometre 2
	udpFrame[4] = kilometer & 0x0000FF00; // kilometre 3
    udpFrame[5] = kilometer & 0x000000FF; // kilometre 4
    udpFrame[6] = speed; // vitesse
    udpFrame[7] = fuel; // niveau fuel
	udpFrame[8] = rpm & 0xFF00; // rpm1
    udpFrame[9] = rpm & 0x00FF; // rpm2
}