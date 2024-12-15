#include "data_management.h"
#include <stddef.h>

uint8_t get_cmd_warning_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x80) >> 7; }
void set_cmd_warning_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x80; *instance |= value << 7; }
uint8_t get_cmd_position_light_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x40) >> 6; }
void set_cmd_position_light_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x40; *instance |= value << 6; }
uint8_t get_cmd_low_beam_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x20) >> 5; }
void set_cmd_low_beam_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x20; *instance |= value << 5; }
uint8_t get_cmd_high_beam_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x10) >> 4; }
void set_cmd_high_beam_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x10; *instance |= value << 4; }
uint8_t get_cmd_right_indicator_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x08) >> 3; }
void set_cmd_right_indicator_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x08; *instance |= value << 3; }
uint8_t get_cmd_left_indicator_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x04) >> 2; }
void set_cmd_left_indicator_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x04; *instance |= value << 2; }
uint8_t get_cmd_wipers_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x02) >> 1; }
void set_cmd_wipers_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x02; *instance |= value << 1; }
uint8_t get_cmd_washer_from_comodo_frame_t(comodo_frame_t instance) { return (instance & 0x01) >> 0; }
void set_cmd_washer_in_comodo_frame_t(comodo_frame_t* instance, int value) { *instance &= ~0x01; *instance |= value << 0; }


uint16_t get_position_light_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x8000) >> 15; }
void set_position_light_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x8000; *instance |= value << 15; }
uint16_t get_low_beam_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x4000) >> 14; }
void set_low_beam_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x4000; *instance |= value << 14; }
uint16_t get_high_beam_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x2000) >> 13; }
void set_high_beam_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x2000; *instance |= value << 13; }
uint16_t get_fuel_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x1000) >> 12; }
void set_fuel_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x1000; *instance |= value << 12; }
uint16_t get_motor_issue_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0800) >> 11; }
void set_motor_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0800; *instance |= value << 11; }
uint16_t get_pressure_issue_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0400) >> 10; }
void set_pressure_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0400; *instance |= value << 10; }
uint16_t get_unused_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0200) >> 9; }
void set_unused_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0200; *instance |= value << 9; }
uint16_t get_discharged_battery_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0100) >> 8; }
void set_discharged_battery_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0100; *instance |= value << 8; }
uint16_t get_warning_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0080) >> 7; }
void set_warning_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0080; *instance |= value << 7; }
uint16_t get_battery_issue_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0040) >> 6; }
void set_battery_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0040; *instance |= value << 6; }
uint16_t get_coolant_temperature_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0020) >> 5; }
void set_coolant_temperature_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0020; *instance |= value << 5; }
uint16_t get_motor_pressure_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0010) >> 4; }
void set_motor_pressure_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0010; *instance |= value << 4; }
uint16_t get_oil_overheat_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0008) >> 3; }
void set_oil_overheat_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0008; *instance |= value << 3; }
uint16_t get_brake_issue_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0004) >> 2; }
void set_brake_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0004; *instance |= value << 2; }
uint16_t get_wiper_active_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0002) >> 1; }
void set_wiper_active_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0002; *instance |= value << 1; }
uint16_t get_washer_active_from_dashboard_light_t(dashboard_light_t instance) { return (instance & 0x0001) >> 0; }
void set_washer_active_in_dashboard_light_t(dashboard_light_t* instance, int value) { *instance &= ~0x0001; *instance |= value << 0; }


