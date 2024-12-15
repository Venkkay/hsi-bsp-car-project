#include "data_management.h"
#include <stdint.h>

/**
 * Set the value of bgf_trame_t.
 *
 * @param[out] instance An instance of bgf_trame_t.
 * @return Return void.
 */
void set_bgf_trame_t(bgf_trame_t* instance, uint16_t value) {
    *instance = value;
}

/**
 * Set the value of kilometer_t.
 *
 * @param[out] instance An instance of kilometer_t.
 * @return Return void.
 */
void set_kilometer_t(kilometer_t* instance, uint32_t value) {
    *instance = value;
}

/**
 * Set the value of rpm_t.
 *
 * @param[out] instance An instance of rpm_t.
 * @return Return void.
 */
void set_rpm_t(rpm_t* instance, uint32_t value) {
    if (value >= 0 && value <= 10000) {
        *instance = value;
    }
}

/**
 * Set the value of rpm_dashboard_t.
 *
 * @param[out] instance An instance of rpm_dashboard_t.
 * @return Return void.
 */
void set_rpm_dashboard_t(rpm_dashboard_t* instance, uint16_t value) {
    if (value >= 0 && value <= 1000) {
        *instance = value;
    }
}

/**
 * Set the value of fuel_t.
 *
 * @param[out] instance An instance of fuel_t.
 * @return Return void.
 */
void set_fuel_t(fuel_t* instance, uint8_t value) {
    if (value >= 0 && value <= 40) {
        *instance = value;
    }
}

/**
 * Set the value of fuel_percent_t.
 *
 * @param[out] instance An instance of fuel_percent_t.
 * @return Return void.
 */
void set_fuel_percent_t(fuel_percent_t* instance, uint8_t value) {
    if (value >= 0 && value <= 100) {
        *instance = value;
    }
}

/**
 * Set the value of mux_frame_number_t.
 *
 * @param[out] instance An instance of mux_frame_number_t.
 * @return Return void.
 */
void set_mux_frame_number_t(mux_frame_number_t* instance, uint8_t value) {
    if (value >= 1 && value <= 100) {
        *instance = value;
    }
}

/**
 * Set the value of speed_t.
 *
 * @param[out] instance An instance of speed_t.
 * @return Return void.
 */
void set_speed_t(speed_t* instance, uint8_t value) {
    if (value >= 0 && value <= 255) {
        *instance = value;
    }
}

/**
 * Set the value of crc8_t.
 *
 * @param[out] instance An instance of crc8_t.
 * @return Return void.
 */
void set_crc8_t(crc8_t* instance, uint8_t value) {
    *instance = value;
}

// Flags for comodo_frame_t.

/**
 * Get cmd_warning flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_warning_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x80) >> 7;
}
/**
 * Set cmd_warning flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_warning_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x80;
    *instance |= value << 7;
}

/**
 * Get cmd_position_light flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_position_light_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x40) >> 6;
}
/**
 * Set cmd_position_light flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_position_light_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x40;
    *instance |= value << 6;
}

/**
 * Get cmd_low_beam flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_low_beam_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x20) >> 5;
}
/**
 * Set cmd_low_beam flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_low_beam_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x20;
    *instance |= value << 5;
}

/**
 * Get cmd_high_beam flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_high_beam_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x10) >> 4;
}
/**
 * Set cmd_high_beam flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_high_beam_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x10;
    *instance |= value << 4;
}

/**
 * Get cmd_right_indicator flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_right_indicator_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x08) >> 3;
}
/**
 * Set cmd_right_indicator flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_right_indicator_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x08;
    *instance |= value << 3;
}

/**
 * Get cmd_left_indicator flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_left_indicator_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x04) >> 2;
}
/**
 * Set cmd_left_indicator flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_left_indicator_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x04;
    *instance |= value << 2;
}

/**
 * Get cmd_wipers flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_wipers_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x02) >> 1;
}
/**
 * Set cmd_wipers flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_wipers_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x02;
    *instance |= value << 1;
}

/**
 * Get cmd_washer flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return Return the value of the got flag.
 */
uint8_t get_cmd_washer_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x01) >> 0;
}
/**
 * Set cmd_washer flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_cmd_washer_in_comodo_frame_t(comodo_frame_t* instance, int value) {
    *instance &= ~0x01;
    *instance |= value << 0;
}

/**
 * Set all flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return void.
 */
void set_comodo_frame_t(comodo_frame_t* instance, comodo_frame_t value) {
    *instance = value;
}



// Flags for dashboard_light_t.

/**
 * Get position_light flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_position_light_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x8000) >> 15;
}
/**
 * Set position_light flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_position_light_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x8000;
    *instance |= value << 15;
}

/**
 * Get low_beam flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_low_beam_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x4000) >> 14;
}
/**
 * Set low_beam flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_low_beam_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x4000;
    *instance |= value << 14;
}

/**
 * Get high_beam flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_high_beam_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x2000) >> 13;
}
/**
 * Set high_beam flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_high_beam_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x2000;
    *instance |= value << 13;
}

/**
 * Get fuel flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_fuel_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x1000) >> 12;
}
/**
 * Set fuel flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_fuel_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x1000;
    *instance |= value << 12;
}

/**
 * Get motor_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_motor_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0800) >> 11;
}
/**
 * Set motor_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_motor_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0800;
    *instance |= value << 11;
}

/**
 * Get pressure_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_pressure_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0400) >> 10;
}
/**
 * Set pressure_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_pressure_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0400;
    *instance |= value << 10;
}

/**
 * Get unused flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_unused_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0200) >> 9;
}
/**
 * Set unused flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_unused_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0200;
    *instance |= value << 9;
}

/**
 * Get discharged_battery flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_discharged_battery_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0100) >> 8;
}
/**
 * Set discharged_battery flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_discharged_battery_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0100;
    *instance |= value << 8;
}

/**
 * Get warning flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_warning_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0080) >> 7;
}
/**
 * Set warning flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_warning_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0080;
    *instance |= value << 7;
}

/**
 * Get battery_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_battery_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0040) >> 6;
}
/**
 * Set battery_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_battery_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0040;
    *instance |= value << 6;
}

/**
 * Get coolant_temperature flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_coolant_temperature_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0020) >> 5;
}
/**
 * Set coolant_temperature flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_coolant_temperature_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0020;
    *instance |= value << 5;
}

/**
 * Get motor_pressure flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_motor_pressure_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0010) >> 4;
}
/**
 * Set motor_pressure flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_motor_pressure_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0010;
    *instance |= value << 4;
}

/**
 * Get oil_overheat flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_oil_overheat_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0008) >> 3;
}
/**
 * Set oil_overheat flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_oil_overheat_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0008;
    *instance |= value << 3;
}

/**
 * Get brake_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_brake_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0004) >> 2;
}
/**
 * Set brake_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_brake_issue_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0004;
    *instance |= value << 2;
}

/**
 * Get wiper_active flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_wiper_active_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0002) >> 1;
}
/**
 * Set wiper_active flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_wiper_active_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0002;
    *instance |= value << 1;
}

/**
 * Get washer_active flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return Return the value of the got flag.
 */
uint16_t get_washer_active_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0001) >> 0;
}
/**
 * Set washer_active flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_washer_active_in_dashboard_light_t(dashboard_light_t* instance, int value) {
    *instance &= ~0x0001;
    *instance |= value << 0;
}

/**
 * Set all flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return void.
 */
void set_dashboard_light_t(dashboard_light_t* instance, dashboard_light_t value) {
    *instance = value;
}



// Enums Setter

/**
 * Set the value of chassis_issues_t.
 *
 * @param[out] instance An instance of chassis_issues_t.
 * @return Return void.
 */
void set_chassis_issues_t(chassis_issues_t* instance, chassis_issues_t value) {
    *instance = value;
}



/**
 * Set the value of engine_issues_t.
 *
 * @param[out] instance An instance of engine_issues_t.
 * @return Return void.
 */
void set_engine_issues_t(engine_issues_t* instance, engine_issues_t value) {
    *instance = value;
}



/**
 * Set the value of battery_issues_t.
 *
 * @param[out] instance An instance of battery_issues_t.
 * @return Return void.
 */
void set_battery_issues_t(battery_issues_t* instance, battery_issues_t value) {
    *instance = value;
}



/**
 * Set the value of bgf_message_t.
 *
 * @param[out] instance An instance of bgf_message_t.
 * @return Return void.
 */
void set_bgf_message_t(bgf_message_t* instance, bgf_message_t value) {
    *instance = value;
}



/**
 * Set the value of light_status_t.
 *
 * @param[out] instance An instance of light_status_t.
 * @return Return void.
 */
void set_light_status_t(light_status_t* instance, light_status_t value) {
    *instance = value;
}



/**
 * Set the value of light_state_t.
 *
 * @param[out] instance An instance of light_state_t.
 * @return Return void.
 */
void set_light_state_t(light_state_t* instance, light_state_t value) {
    *instance = value;
}



/**
 * Set the value of indicator_state_t.
 *
 * @param[out] instance An instance of indicator_state_t.
 * @return Return void.
 */
void set_indicator_state_t(indicator_state_t* instance, indicator_state_t value) {
    *instance = value;
}



/**
 * Set the value of windscreen_wipers_state_t.
 *
 * @param[out] instance An instance of windscreen_wipers_state_t.
 * @return Return void.
 */
void set_windscreen_wipers_state_t(windscreen_wipers_state_t* instance, windscreen_wipers_state_t value) {
    *instance = value;
}



// Struct getter and setter

/**
 * Get kilometer flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
kilometer_t get_kilometer_from_mux_frame_t(mux_frame_t instance) {
    return instance.kilometer;
}
/**
 * Set kilometer flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_kilometer_in_mux_frame_t(mux_frame_t* instance, kilometer_t value) {
    set_kilometer_t(&instance->kilometer, value);
}

/**
 * Get rpm flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
rpm_t get_rpm_from_mux_frame_t(mux_frame_t instance) {
    return instance.rpm;
}
/**
 * Set rpm flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_rpm_in_mux_frame_t(mux_frame_t* instance, rpm_t value) {
    set_rpm_t(&instance->rpm, value);
}

/**
 * Get fuel_level flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
fuel_t get_fuel_level_from_mux_frame_t(mux_frame_t instance) {
    return instance.fuel_level;
}
/**
 * Set fuel_level flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_fuel_level_in_mux_frame_t(mux_frame_t* instance, fuel_t value) {
    set_fuel_t(&instance->fuel_level, value);
}

/**
 * Get frame_number flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
mux_frame_number_t get_frame_number_from_mux_frame_t(mux_frame_t instance) {
    return instance.frame_number;
}
/**
 * Set frame_number flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_frame_number_in_mux_frame_t(mux_frame_t* instance, mux_frame_number_t value) {
    set_mux_frame_number_t(&instance->frame_number, value);
}

/**
 * Get speed flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
speed_t get_speed_from_mux_frame_t(mux_frame_t instance) {
    return instance.speed;
}
/**
 * Set speed flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_speed_in_mux_frame_t(mux_frame_t* instance, speed_t value) {
    set_speed_t(&instance->speed, value);
}

/**
 * Get chassis_issue flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
chassis_issues_t get_chassis_issue_from_mux_frame_t(mux_frame_t instance) {
    return instance.chassis_issue;
}
/**
 * Set chassis_issue flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_chassis_issue_in_mux_frame_t(mux_frame_t* instance, chassis_issues_t value) {
    set_chassis_issues_t(&instance->chassis_issue, value);
}

/**
 * Get engine_issue flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
engine_issues_t get_engine_issue_from_mux_frame_t(mux_frame_t instance) {
    return instance.engine_issue;
}
/**
 * Set engine_issue flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_engine_issue_in_mux_frame_t(mux_frame_t* instance, engine_issues_t value) {
    set_engine_issues_t(&instance->engine_issue, value);
}

/**
 * Get battery_issue flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
battery_issues_t get_battery_issue_from_mux_frame_t(mux_frame_t instance) {
    return instance.battery_issue;
}
/**
 * Set battery_issue flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_battery_issue_in_mux_frame_t(mux_frame_t* instance, battery_issues_t value) {
    set_battery_issues_t(&instance->battery_issue, value);
}

/**
 * Get crc8 flag from mux_frame_t.
 *
 * @param[in] instance An instance of mux_frame_t.
 * @return Return the value of the got flag.
 */
crc8_t get_crc8_from_mux_frame_t(mux_frame_t instance) {
    return instance.crc8;
}
/**
 * Set crc8 flag in mux_frame_t.
 *
 * @param[out] instance An instance of mux_frame_t.
 * @return Return void.
 */
void set_crc8_in_mux_frame_t(mux_frame_t* instance, crc8_t value) {
    set_crc8_t(&instance->crc8, value);
}



/**
 * Get kilometer flag from bcgv_frame_t.
 *
 * @param[in] instance An instance of bcgv_frame_t.
 * @return Return the value of the got flag.
 */
kilometer_t get_kilometer_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.kilometer;
}
/**
 * Set kilometer flag in bcgv_frame_t.
 *
 * @param[out] instance An instance of bcgv_frame_t.
 * @return Return void.
 */
void set_kilometer_in_bcgv_frame_t(bcgv_frame_t* instance, kilometer_t value) {
    set_kilometer_t(&instance->kilometer, value);
}

/**
 * Get rpm flag from bcgv_frame_t.
 *
 * @param[in] instance An instance of bcgv_frame_t.
 * @return Return the value of the got flag.
 */
rpm_dashboard_t get_rpm_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.rpm;
}
/**
 * Set rpm flag in bcgv_frame_t.
 *
 * @param[out] instance An instance of bcgv_frame_t.
 * @return Return void.
 */
void set_rpm_in_bcgv_frame_t(bcgv_frame_t* instance, rpm_dashboard_t value) {
    set_rpm_dashboard_t(&instance->rpm, value);
}

/**
 * Get speed flag from bcgv_frame_t.
 *
 * @param[in] instance An instance of bcgv_frame_t.
 * @return Return the value of the got flag.
 */
speed_t get_speed_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.speed;
}
/**
 * Set speed flag in bcgv_frame_t.
 *
 * @param[out] instance An instance of bcgv_frame_t.
 * @return Return void.
 */
void set_speed_in_bcgv_frame_t(bcgv_frame_t* instance, speed_t value) {
    set_speed_t(&instance->speed, value);
}

/**
 * Get fuel_percent_level flag from bcgv_frame_t.
 *
 * @param[in] instance An instance of bcgv_frame_t.
 * @return Return the value of the got flag.
 */
fuel_t get_fuel_percent_level_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.fuel_percent_level;
}
/**
 * Set fuel_percent_level flag in bcgv_frame_t.
 *
 * @param[out] instance An instance of bcgv_frame_t.
 * @return Return void.
 */
void set_fuel_percent_level_in_bcgv_frame_t(bcgv_frame_t* instance, fuel_t value) {
    set_fuel_t(&instance->fuel_percent_level, value);
}

/**
 * Get dashboard_light flag from bcgv_frame_t.
 *
 * @param[in] instance An instance of bcgv_frame_t.
 * @return Return the value of the got flag.
 */
dashboard_light_t get_dashboard_light_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.dashboard_light;
}
/**
 * Set dashboard_light flag in bcgv_frame_t.
 *
 * @param[out] instance An instance of bcgv_frame_t.
 * @return Return void.
 */
void set_dashboard_light_in_bcgv_frame_t(bcgv_frame_t* instance, dashboard_light_t value) {
    set_dashboard_light_t(&instance->dashboard_light, value);
}



