#include "data_management.h"
#include <stdint.h>
#include <stdbool.h>

bool set_bgf_frame_t(bgf_frame_t* instance, const uint16_t value) {
    *instance = value;
    return true;
}

bool set_kilometer_t(kilometer_t* instance, const uint32_t value) {
    *instance = value;
    return true;
}

bool check_rpm_t(const uint32_t value){
    if (value > 10000) { return false; }
    return true;
}

bool set_rpm_t(rpm_t* instance, const uint32_t value) {
    if (check_rpm_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_rpm_dashboard_t(const uint16_t value){
    if (value > 1000) { return false; }
    return true;
}

bool set_rpm_dashboard_t(rpm_dashboard_t* instance, const uint16_t value) {
    if (check_rpm_dashboard_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_fuel_t(const uint8_t value){
    if (value > 40) { return false; }
    return true;
}

bool set_fuel_t(fuel_t* instance, const uint8_t value) {
    if (check_fuel_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_fuel_percent_t(const uint8_t value){
    if (value > 100) { return false; }
    return true;
}

bool set_fuel_percent_t(fuel_percent_t* instance, const uint8_t value) {
    if (check_fuel_percent_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_mux_frame_number_t(const uint8_t value){
    if (value < 1) { return false; }
    if (value > 100) { return false; }
    return true;
}

bool set_mux_frame_number_t(mux_frame_number_t* instance, const uint8_t value) {
    if (check_mux_frame_number_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool set_speed_t(speed_t* instance, const uint8_t value) {
    *instance = value;
    return true;
}

bool set_crc8_t(crc8_t* instance, const uint8_t value) {
    *instance = value;
    return true;
}

// Flags for comodo_frame_t.

uint8_t get_cmd_warning_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x80) >> 7;
}
bool check_cmd_warning_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_warning_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_warning_in_comodo_frame_t(value)) {
        *instance &= ~0x80;
        *instance |= value << 7;
        return true;
    }
    return false;
}

uint8_t get_cmd_position_light_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x40) >> 6;
}
bool check_cmd_position_light_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_position_light_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_position_light_in_comodo_frame_t(value)) {
        *instance &= ~0x40;
        *instance |= value << 6;
        return true;
    }
    return false;
}

uint8_t get_cmd_low_beam_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x20) >> 5;
}
bool check_cmd_low_beam_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_low_beam_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_low_beam_in_comodo_frame_t(value)) {
        *instance &= ~0x20;
        *instance |= value << 5;
        return true;
    }
    return false;
}

uint8_t get_cmd_high_beam_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x10) >> 4;
}
bool check_cmd_high_beam_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_high_beam_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_high_beam_in_comodo_frame_t(value)) {
        *instance &= ~0x10;
        *instance |= value << 4;
        return true;
    }
    return false;
}

uint8_t get_cmd_right_indicator_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x08) >> 3;
}
bool check_cmd_right_indicator_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_right_indicator_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_right_indicator_in_comodo_frame_t(value)) {
        *instance &= ~0x08;
        *instance |= value << 3;
        return true;
    }
    return false;
}

uint8_t get_cmd_left_indicator_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x04) >> 2;
}
bool check_cmd_left_indicator_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_left_indicator_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_left_indicator_in_comodo_frame_t(value)) {
        *instance &= ~0x04;
        *instance |= value << 2;
        return true;
    }
    return false;
}

uint8_t get_cmd_wipers_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x02) >> 1;
}
bool check_cmd_wipers_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_wipers_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_wipers_in_comodo_frame_t(value)) {
        *instance &= ~0x02;
        *instance |= value << 1;
        return true;
    }
    return false;
}

uint8_t get_cmd_washer_from_comodo_frame_t(const comodo_frame_t instance) {
    return (instance & 0x01) >> 0;
}
bool check_cmd_washer_in_comodo_frame_t(const uint8_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_cmd_washer_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value) {
    if(check_cmd_washer_in_comodo_frame_t(value)) {
        *instance &= ~0x01;
        *instance |= value << 0;
        return true;
    }
    return false;
}

bool set_all_flag_comodo_frame_t(comodo_frame_t* instance, const uint8_t cmd_warning, const uint8_t cmd_position_light, const uint8_t cmd_low_beam, const uint8_t cmd_high_beam, const uint8_t cmd_right_indicator, const uint8_t cmd_left_indicator, const uint8_t cmd_wipers, const uint8_t cmd_washer) {
    set_cmd_warning_in_comodo_frame_t(instance, cmd_warning);
    set_cmd_position_light_in_comodo_frame_t(instance, cmd_position_light);
    set_cmd_low_beam_in_comodo_frame_t(instance, cmd_low_beam);
    set_cmd_high_beam_in_comodo_frame_t(instance, cmd_high_beam);
    set_cmd_right_indicator_in_comodo_frame_t(instance, cmd_right_indicator);
    set_cmd_left_indicator_in_comodo_frame_t(instance, cmd_left_indicator);
    set_cmd_wipers_in_comodo_frame_t(instance, cmd_wipers);
    set_cmd_washer_in_comodo_frame_t(instance, cmd_washer);
    return true;
}

bool check_comodo_frame_t(const uint8_t value){
    if(value) {
        return true;
    }
    return false;
}
  
bool set_comodo_frame_t(comodo_frame_t* instance, const comodo_frame_t value) {
    if (check_comodo_frame_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}



// Flags for dashboard_light_t.

uint16_t get_position_light_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x8000) >> 15;
}
bool check_position_light_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_position_light_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_position_light_in_dashboard_light_t(value)) {
        *instance &= ~0x8000;
        *instance |= value << 15;
        return true;
    }
    return false;
}

uint16_t get_low_beam_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x4000) >> 14;
}
bool check_low_beam_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_low_beam_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_low_beam_in_dashboard_light_t(value)) {
        *instance &= ~0x4000;
        *instance |= value << 14;
        return true;
    }
    return false;
}

uint16_t get_high_beam_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x2000) >> 13;
}
bool check_high_beam_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_high_beam_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_high_beam_in_dashboard_light_t(value)) {
        *instance &= ~0x2000;
        *instance |= value << 13;
        return true;
    }
    return false;
}

uint16_t get_fuel_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x1000) >> 12;
}
bool check_fuel_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_fuel_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_fuel_in_dashboard_light_t(value)) {
        *instance &= ~0x1000;
        *instance |= value << 12;
        return true;
    }
    return false;
}

uint16_t get_motor_issue_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0800) >> 11;
}
bool check_motor_issue_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_motor_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_motor_issue_in_dashboard_light_t(value)) {
        *instance &= ~0x0800;
        *instance |= value << 11;
        return true;
    }
    return false;
}

uint16_t get_pressure_issue_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0400) >> 10;
}
bool check_pressure_issue_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_pressure_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_pressure_issue_in_dashboard_light_t(value)) {
        *instance &= ~0x0400;
        *instance |= value << 10;
        return true;
    }
    return false;
}

uint16_t get_unused_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0200) >> 9;
}
bool check_unused_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_unused_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_unused_in_dashboard_light_t(value)) {
        *instance &= ~0x0200;
        *instance |= value << 9;
        return true;
    }
    return false;
}

uint16_t get_discharged_battery_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0100) >> 8;
}
bool check_discharged_battery_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_discharged_battery_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_discharged_battery_in_dashboard_light_t(value)) {
        *instance &= ~0x0100;
        *instance |= value << 8;
        return true;
    }
    return false;
}

uint16_t get_warning_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0080) >> 7;
}
bool check_warning_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_warning_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_warning_in_dashboard_light_t(value)) {
        *instance &= ~0x0080;
        *instance |= value << 7;
        return true;
    }
    return false;
}

uint16_t get_battery_issue_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0040) >> 6;
}
bool check_battery_issue_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_battery_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_battery_issue_in_dashboard_light_t(value)) {
        *instance &= ~0x0040;
        *instance |= value << 6;
        return true;
    }
    return false;
}

uint16_t get_coolant_temperature_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0020) >> 5;
}
bool check_coolant_temperature_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_coolant_temperature_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_coolant_temperature_in_dashboard_light_t(value)) {
        *instance &= ~0x0020;
        *instance |= value << 5;
        return true;
    }
    return false;
}

uint16_t get_motor_pressure_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0010) >> 4;
}
bool check_motor_pressure_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_motor_pressure_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_motor_pressure_in_dashboard_light_t(value)) {
        *instance &= ~0x0010;
        *instance |= value << 4;
        return true;
    }
    return false;
}

uint16_t get_oil_overheat_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0008) >> 3;
}
bool check_oil_overheat_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_oil_overheat_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_oil_overheat_in_dashboard_light_t(value)) {
        *instance &= ~0x0008;
        *instance |= value << 3;
        return true;
    }
    return false;
}

uint16_t get_brake_issue_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0004) >> 2;
}
bool check_brake_issue_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_brake_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_brake_issue_in_dashboard_light_t(value)) {
        *instance &= ~0x0004;
        *instance |= value << 2;
        return true;
    }
    return false;
}

uint16_t get_wiper_active_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0002) >> 1;
}
bool check_wiper_active_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_wiper_active_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_wiper_active_in_dashboard_light_t(value)) {
        *instance &= ~0x0002;
        *instance |= value << 1;
        return true;
    }
    return false;
}

uint16_t get_washer_active_from_dashboard_light_t(const dashboard_light_t instance) {
    return (instance & 0x0001) >> 0;
}
bool check_washer_active_in_dashboard_light_t(const uint16_t value){
    if(value >> 1 != 0) {
        return false;
    }
    return true;
}
bool set_washer_active_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value) {
    if(check_washer_active_in_dashboard_light_t(value)) {
        *instance &= ~0x0001;
        *instance |= value << 0;
        return true;
    }
    return false;
}

bool set_all_flag_dashboard_light_t(dashboard_light_t* instance, const uint16_t position_light, const uint16_t low_beam, const uint16_t high_beam, const uint16_t fuel, const uint16_t motor_issue, const uint16_t pressure_issue, const uint16_t unused, const uint16_t discharged_battery, const uint16_t warning, const uint16_t battery_issue, const uint16_t coolant_temperature, const uint16_t motor_pressure, const uint16_t oil_overheat, const uint16_t brake_issue, const uint16_t wiper_active, const uint16_t washer_active) {
    set_position_light_in_dashboard_light_t(instance, position_light);
    set_low_beam_in_dashboard_light_t(instance, low_beam);
    set_high_beam_in_dashboard_light_t(instance, high_beam);
    set_fuel_in_dashboard_light_t(instance, fuel);
    set_motor_issue_in_dashboard_light_t(instance, motor_issue);
    set_pressure_issue_in_dashboard_light_t(instance, pressure_issue);
    set_unused_in_dashboard_light_t(instance, unused);
    set_discharged_battery_in_dashboard_light_t(instance, discharged_battery);
    set_warning_in_dashboard_light_t(instance, warning);
    set_battery_issue_in_dashboard_light_t(instance, battery_issue);
    set_coolant_temperature_in_dashboard_light_t(instance, coolant_temperature);
    set_motor_pressure_in_dashboard_light_t(instance, motor_pressure);
    set_oil_overheat_in_dashboard_light_t(instance, oil_overheat);
    set_brake_issue_in_dashboard_light_t(instance, brake_issue);
    set_wiper_active_in_dashboard_light_t(instance, wiper_active);
    set_washer_active_in_dashboard_light_t(instance, washer_active);
    return true;
}

bool check_dashboard_light_t(const uint16_t value){
    if(value) {
        return true;
    }
    return false;
}
  
bool set_dashboard_light_t(dashboard_light_t* instance, const dashboard_light_t value) {
    if (check_dashboard_light_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}



// Enums Setter

bool check_chassis_issues_t(const uint8_t value){
    if(!(value == NOTHING_CHASSIS || value == TIRES_PRESSURE || value == BRAKE_FAILURE)) {
        return false;
    }
    return true;
}

bool set_chassis_issues_t(chassis_issues_t* instance, const uint8_t value) {
    if (check_chassis_issues_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_engine_issues_t(const uint8_t value){
    if(!(value == NOTHING_ENGINE || value == PRESSURE_FAULT || value == COOLANT_TEMPERATURE || value == OIL_OVERHEATING)) {
        return false;
    }
    return true;
}

bool set_engine_issues_t(engine_issues_t* instance, const uint8_t value) {
    if (check_engine_issues_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_battery_issues_t(const uint8_t value){
    if(!(value == NOTHING_BATTERY || value == UNLOADED || value == OUTAGE)) {
        return false;
    }
    return true;
}

bool set_battery_issues_t(battery_issues_t* instance, const uint8_t value) {
    if (check_battery_issues_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_bgf_message_t(const uint8_t value){
    if(!(value == POSITION_LIGHT || value == LOW_BEAM || value == HIGH_BEAM || value == RIGHT_INDICATOR || value == LEFT_INDICATOR)) {
        return false;
    }
    return true;
}

bool set_bgf_message_t(bgf_message_t* instance, const uint8_t value) {
    if (check_bgf_message_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_light_status_t(const uint8_t value){
    if(!(value == OFF || value == ON)) {
        return false;
    }
    return true;
}

bool set_light_status_t(light_status_t* instance, const uint8_t value) {
    if (check_light_status_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_light_state_t(const uint8_t value){
    if(!(value == LIGHT_OFF || value == LIGHT_ON || value == LIGHT_ERROR || value == LIGHT_ACQUITTED)) {
        return false;
    }
    return true;
}

bool set_light_state_t(light_state_t* instance, const uint8_t value) {
    if (check_light_state_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_indicator_state_t(const uint8_t value){
    if(!(value == INDICATOR_OFF || value == ACTIVATED_OFF || value == ACTIVATED_ON || value == INDICATOR_ERROR || value == INDICATOR_ACQUITTED)) {
        return false;
    }
    return true;
}

bool set_indicator_state_t(indicator_state_t* instance, const uint8_t value) {
    if (check_indicator_state_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

bool check_windscreen_wipers_state_t(const uint8_t value){
    if(!(value == ALL_OFF || value == WIPERS_ACTIVATED || value == WDSCRN_CLN_WPRS_ACTIVATED || value == TMR_WPRS_WDSCRN_CLN_OFF)) {
        return false;
    }
    return true;
}

bool set_windscreen_wipers_state_t(windscreen_wipers_state_t* instance, const uint8_t value) {
    if (check_windscreen_wipers_state_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

// Struct getter and setter

kilometer_t get_kilometer_from_mux_frame_t(const mux_frame_t instance) {
    return instance.kilometer;
}
bool set_kilometer_in_mux_frame_t(mux_frame_t* instance, const uint32_t value) {
    return set_kilometer_t(&instance->kilometer, value);
}

rpm_t get_rpm_from_mux_frame_t(const mux_frame_t instance) {
    return instance.rpm;
}
bool set_rpm_in_mux_frame_t(mux_frame_t* instance, const uint32_t value) {
    return set_rpm_t(&instance->rpm, value);
}

fuel_t get_fuel_level_from_mux_frame_t(const mux_frame_t instance) {
    return instance.fuel_level;
}
bool set_fuel_level_in_mux_frame_t(mux_frame_t* instance, const uint8_t value) {
    return set_fuel_t(&instance->fuel_level, value);
}

mux_frame_number_t get_frame_number_from_mux_frame_t(const mux_frame_t instance) {
    return instance.frame_number;
}
bool set_frame_number_in_mux_frame_t(mux_frame_t* instance, const uint8_t value) {
    return set_mux_frame_number_t(&instance->frame_number, value);
}

speed_t get_speed_from_mux_frame_t(const mux_frame_t instance) {
    return instance.speed;
}
bool set_speed_in_mux_frame_t(mux_frame_t* instance, const uint8_t value) {
    return set_speed_t(&instance->speed, value);
}

chassis_issues_t get_chassis_issue_from_mux_frame_t(const mux_frame_t instance) {
    return instance.chassis_issue;
}
bool set_chassis_issue_in_mux_frame_t(mux_frame_t* instance, const uint8_t value) {
    return set_chassis_issues_t(&instance->chassis_issue, value);
}

engine_issues_t get_engine_issue_from_mux_frame_t(const mux_frame_t instance) {
    return instance.engine_issue;
}
bool set_engine_issue_in_mux_frame_t(mux_frame_t* instance, const uint8_t value) {
    return set_engine_issues_t(&instance->engine_issue, value);
}

battery_issues_t get_battery_issue_from_mux_frame_t(const mux_frame_t instance) {
    return instance.battery_issue;
}
bool set_battery_issue_in_mux_frame_t(mux_frame_t* instance, const uint8_t value) {
    return set_battery_issues_t(&instance->battery_issue, value);
}

crc8_t get_crc8_from_mux_frame_t(const mux_frame_t instance) {
    return instance.crc8;
}
bool set_crc8_in_mux_frame_t(mux_frame_t* instance, const uint8_t value) {
    return set_crc8_t(&instance->crc8, value);
}

bool check_mux_frame_t(const rpm_t rpm, const fuel_t fuel_level, const mux_frame_number_t frame_number) {
    if (!check_rpm_t(rpm)) { return false;}
    if (!check_fuel_t(fuel_level)) { return false;}
    if (!check_mux_frame_number_t(frame_number)) { return false;}
    return true;
}


bool set_mux_frame_t(mux_frame_t* instance, kilometer_t kilometer, rpm_t rpm, fuel_t fuel_level, mux_frame_number_t frame_number, speed_t speed, chassis_issues_t chassis_issue, engine_issues_t engine_issue, battery_issues_t battery_issue, crc8_t crc8) {
    if (!check_mux_frame_t(rpm, fuel_level, frame_number)) {
        return false;
    }
    set_kilometer_in_mux_frame_t(instance, kilometer);
    set_rpm_in_mux_frame_t(instance, rpm);
    set_fuel_level_in_mux_frame_t(instance, fuel_level);
    set_frame_number_in_mux_frame_t(instance, frame_number);
    set_speed_in_mux_frame_t(instance, speed);
    set_chassis_issue_in_mux_frame_t(instance, chassis_issue);
    set_engine_issue_in_mux_frame_t(instance, engine_issue);
    set_battery_issue_in_mux_frame_t(instance, battery_issue);
    set_crc8_in_mux_frame_t(instance, crc8);
    return true;
}




kilometer_t get_kilometer_from_bcgv_frame_t(const bcgv_frame_t instance) {
    return instance.kilometer;
}
bool set_kilometer_in_bcgv_frame_t(bcgv_frame_t* instance, const uint32_t value) {
    return set_kilometer_t(&instance->kilometer, value);
}

rpm_dashboard_t get_rpm_from_bcgv_frame_t(const bcgv_frame_t instance) {
    return instance.rpm;
}
bool set_rpm_in_bcgv_frame_t(bcgv_frame_t* instance, const uint16_t value) {
    return set_rpm_dashboard_t(&instance->rpm, value);
}

speed_t get_speed_from_bcgv_frame_t(const bcgv_frame_t instance) {
    return instance.speed;
}
bool set_speed_in_bcgv_frame_t(bcgv_frame_t* instance, const uint8_t value) {
    return set_speed_t(&instance->speed, value);
}

fuel_percent_t get_fuel_percent_level_from_bcgv_frame_t(const bcgv_frame_t instance) {
    return instance.fuel_percent_level;
}
bool set_fuel_percent_level_in_bcgv_frame_t(bcgv_frame_t* instance, const uint8_t value) {
    return set_fuel_percent_t(&instance->fuel_percent_level, value);
}

dashboard_light_t get_dashboard_light_from_bcgv_frame_t(const bcgv_frame_t instance) {
    return instance.dashboard_light;
}
bool set_dashboard_light_in_bcgv_frame_t(bcgv_frame_t* instance, const uint16_t value) {
    return set_dashboard_light_t(&instance->dashboard_light, value);
}

bool check_bcgv_frame_t(const rpm_dashboard_t rpm, const fuel_percent_t fuel_percent_level) {
    if (!check_rpm_dashboard_t(rpm)) { return false;}
    if (!check_fuel_percent_t(fuel_percent_level)) { return false;}
    return true;
}


bool set_bcgv_frame_t(bcgv_frame_t* instance, kilometer_t kilometer, rpm_dashboard_t rpm, speed_t speed, fuel_percent_t fuel_percent_level, dashboard_light_t dashboard_light) {
    if (!check_bcgv_frame_t(rpm, fuel_percent_level)) {
        return false;
    }
    set_kilometer_in_bcgv_frame_t(instance, kilometer);
    set_rpm_in_bcgv_frame_t(instance, rpm);
    set_speed_in_bcgv_frame_t(instance, speed);
    set_fuel_percent_level_in_bcgv_frame_t(instance, fuel_percent_level);
    set_dashboard_light_in_bcgv_frame_t(instance, dashboard_light);
    return true;
}




