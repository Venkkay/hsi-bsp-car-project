#include "data_management.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * Check the value of bgf_trame_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_bgf_trame_t(uint16_t value){
    return true;
}
  
/**
 * Set the value of bgf_trame_t.
 *
 * \param[out] instance : An instance of bgf_trame_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_bgf_trame_t(bgf_trame_t* instance, uint16_t value) {
    if (check_bgf_trame_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of kilometer_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_kilometer_t(uint32_t value){
    return true;
}
  
/**
 * Set the value of kilometer_t.
 *
 * \param[out] instance : An instance of kilometer_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_kilometer_t(kilometer_t* instance, uint32_t value) {
    if (check_kilometer_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of rpm_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_rpm_t(uint32_t value){
    if (value >= 0 && value <= 10000) {
        return true;
    }
    return false;
}
  
/**
 * Set the value of rpm_t.
 *
 * \param[out] instance : An instance of rpm_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_rpm_t(rpm_t* instance, uint32_t value) {
    if (check_rpm_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of rpm_dashboard_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_rpm_dashboard_t(uint16_t value){
    if (value >= 0 && value <= 1000) {
        return true;
    }
    return false;
}
  
/**
 * Set the value of rpm_dashboard_t.
 *
 * \param[out] instance : An instance of rpm_dashboard_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_rpm_dashboard_t(rpm_dashboard_t* instance, uint16_t value) {
    if (check_rpm_dashboard_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of fuel_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_fuel_t(uint8_t value){
    if (value >= 0 && value <= 40) {
        return true;
    }
    return false;
}
  
/**
 * Set the value of fuel_t.
 *
 * \param[out] instance : An instance of fuel_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_fuel_t(fuel_t* instance, uint8_t value) {
    if (check_fuel_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of fuel_percent_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_fuel_percent_t(uint8_t value){
    if (value >= 0 && value <= 100) {
        return true;
    }
    return false;
}
  
/**
 * Set the value of fuel_percent_t.
 *
 * \param[out] instance : An instance of fuel_percent_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_fuel_percent_t(fuel_percent_t* instance, uint8_t value) {
    if (check_fuel_percent_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of mux_frame_number_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_mux_frame_number_t(uint8_t value){
    if (value >= 1 && value <= 100) {
        return true;
    }
    return false;
}
  
/**
 * Set the value of mux_frame_number_t.
 *
 * \param[out] instance : An instance of mux_frame_number_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_mux_frame_number_t(mux_frame_number_t* instance, uint8_t value) {
    if (check_mux_frame_number_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of speed_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_speed_t(uint8_t value){
    if (value >= 0 && value <= 255) {
        return true;
    }
    return false;
}
  
/**
 * Set the value of speed_t.
 *
 * \param[out] instance : An instance of speed_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_speed_t(speed_t* instance, uint8_t value) {
    if (check_speed_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

/**
 * Check the value of crc8_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_crc8_t(uint8_t value){
    return true;
}
  
/**
 * Set the value of crc8_t.
 *
 * \param[out] instance : An instance of crc8_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_crc8_t(crc8_t* instance, uint8_t value) {
    if (check_crc8_t(value)) {
        *instance = value;
        return true;
    }
    return false;
}

// Flags for comodo_frame_t.

/**
 * Get cmd_warning flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_warning_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x80) >> 7;
}
/**
 * Set cmd_warning flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_warning_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x80;
    *instance |= value << 7;
    return true;
}

/**
 * Get cmd_position_light flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_position_light_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x40) >> 6;
}
/**
 * Set cmd_position_light flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_position_light_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x40;
    *instance |= value << 6;
    return true;
}

/**
 * Get cmd_low_beam flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_low_beam_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x20) >> 5;
}
/**
 * Set cmd_low_beam flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_low_beam_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x20;
    *instance |= value << 5;
    return true;
}

/**
 * Get cmd_high_beam flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_high_beam_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x10) >> 4;
}
/**
 * Set cmd_high_beam flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_high_beam_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x10;
    *instance |= value << 4;
    return true;
}

/**
 * Get cmd_right_indicator flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_right_indicator_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x08) >> 3;
}
/**
 * Set cmd_right_indicator flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_right_indicator_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x08;
    *instance |= value << 3;
    return true;
}

/**
 * Get cmd_left_indicator flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_left_indicator_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x04) >> 2;
}
/**
 * Set cmd_left_indicator flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_left_indicator_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x04;
    *instance |= value << 2;
    return true;
}

/**
 * Get cmd_wipers flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_wipers_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x02) >> 1;
}
/**
 * Set cmd_wipers flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_wipers_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x02;
    *instance |= value << 1;
    return true;
}

/**
 * Get cmd_washer flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_washer_from_comodo_frame_t(comodo_frame_t instance) {
    return (instance & 0x01) >> 0;
}
/**
 * Set cmd_washer flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_washer_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value) {
    *instance &= ~0x01;
    *instance |= value << 0;
    return true;
}

/**
 * Set all flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_all_flag_comodo_frame_t(comodo_frame_t* instance, uint8_t cmd_warning, uint8_t cmd_position_light, uint8_t cmd_low_beam, uint8_t cmd_high_beam, uint8_t cmd_right_indicator, uint8_t cmd_left_indicator, uint8_t cmd_wipers, uint8_t cmd_washer) {
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

/**
 * Check the value of comodo_frame_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_comodo_frame_t(uint8_t value){
    return true;
}
  
/**
 * Set comodo_frame_t.
 *
 * \param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_comodo_frame_t(comodo_frame_t* instance, comodo_frame_t value) {
    *instance = value;
    return true;
}



// Flags for dashboard_light_t.

/**
 * Get position_light flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_position_light_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x8000) >> 15;
}
/**
 * Set position_light flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_position_light_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x8000;
    *instance |= value << 15;
    return true;
}

/**
 * Get low_beam flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_low_beam_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x4000) >> 14;
}
/**
 * Set low_beam flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_low_beam_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x4000;
    *instance |= value << 14;
    return true;
}

/**
 * Get high_beam flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_high_beam_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x2000) >> 13;
}
/**
 * Set high_beam flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_high_beam_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x2000;
    *instance |= value << 13;
    return true;
}

/**
 * Get fuel flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_fuel_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x1000) >> 12;
}
/**
 * Set fuel flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_fuel_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x1000;
    *instance |= value << 12;
    return true;
}

/**
 * Get motor_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_motor_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0800) >> 11;
}
/**
 * Set motor_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_motor_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0800;
    *instance |= value << 11;
    return true;
}

/**
 * Get pressure_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_pressure_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0400) >> 10;
}
/**
 * Set pressure_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_pressure_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0400;
    *instance |= value << 10;
    return true;
}

/**
 * Get unused flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_unused_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0200) >> 9;
}
/**
 * Set unused flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_unused_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0200;
    *instance |= value << 9;
    return true;
}

/**
 * Get discharged_battery flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_discharged_battery_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0100) >> 8;
}
/**
 * Set discharged_battery flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_discharged_battery_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0100;
    *instance |= value << 8;
    return true;
}

/**
 * Get warning flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_warning_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0080) >> 7;
}
/**
 * Set warning flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_warning_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0080;
    *instance |= value << 7;
    return true;
}

/**
 * Get battery_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_battery_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0040) >> 6;
}
/**
 * Set battery_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_battery_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0040;
    *instance |= value << 6;
    return true;
}

/**
 * Get coolant_temperature flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_coolant_temperature_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0020) >> 5;
}
/**
 * Set coolant_temperature flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_coolant_temperature_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0020;
    *instance |= value << 5;
    return true;
}

/**
 * Get motor_pressure flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_motor_pressure_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0010) >> 4;
}
/**
 * Set motor_pressure flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_motor_pressure_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0010;
    *instance |= value << 4;
    return true;
}

/**
 * Get oil_overheat flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_oil_overheat_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0008) >> 3;
}
/**
 * Set oil_overheat flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_oil_overheat_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0008;
    *instance |= value << 3;
    return true;
}

/**
 * Get brake_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_brake_issue_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0004) >> 2;
}
/**
 * Set brake_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_brake_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0004;
    *instance |= value << 2;
    return true;
}

/**
 * Get wiper_active flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_wiper_active_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0002) >> 1;
}
/**
 * Set wiper_active flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_wiper_active_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0002;
    *instance |= value << 1;
    return true;
}

/**
 * Get washer_active flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_washer_active_from_dashboard_light_t(dashboard_light_t instance) {
    return (instance & 0x0001) >> 0;
}
/**
 * Set washer_active flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_washer_active_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value) {
    *instance &= ~0x0001;
    *instance |= value << 0;
    return true;
}

/**
 * Set all flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_all_flag_dashboard_light_t(dashboard_light_t* instance, uint16_t position_light, uint16_t low_beam, uint16_t high_beam, uint16_t fuel, uint16_t motor_issue, uint16_t pressure_issue, uint16_t unused, uint16_t discharged_battery, uint16_t warning, uint16_t battery_issue, uint16_t coolant_temperature, uint16_t motor_pressure, uint16_t oil_overheat, uint16_t brake_issue, uint16_t wiper_active, uint16_t washer_active) {
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

/**
 * Check the value of dashboard_light_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_dashboard_light_t(uint16_t value){
    return true;
}
  
/**
 * Set dashboard_light_t.
 *
 * \param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_dashboard_light_t(dashboard_light_t* instance, dashboard_light_t value) {
    *instance = value;
    return true;
}



// Enums Setter

/**
 * Check the value of chassis_issues_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_chassis_issues_t(chassis_issues_t value){
    return true;
}
  
/**
 * Set the value of chassis_issues_t.
 *
 * \param[out] instance An instance of chassis_issues_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_chassis_issues_t(chassis_issues_t* instance, chassis_issues_t value) {
    *instance = value;
    return true;
}


/**
 * Check the value of engine_issues_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_engine_issues_t(engine_issues_t value){
    return true;
}
  
/**
 * Set the value of engine_issues_t.
 *
 * \param[out] instance An instance of engine_issues_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_engine_issues_t(engine_issues_t* instance, engine_issues_t value) {
    *instance = value;
    return true;
}


/**
 * Check the value of battery_issues_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_battery_issues_t(battery_issues_t value){
    return true;
}
  
/**
 * Set the value of battery_issues_t.
 *
 * \param[out] instance An instance of battery_issues_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_battery_issues_t(battery_issues_t* instance, battery_issues_t value) {
    *instance = value;
    return true;
}


/**
 * Check the value of bgf_message_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_bgf_message_t(bgf_message_t value){
    return true;
}
  
/**
 * Set the value of bgf_message_t.
 *
 * \param[out] instance An instance of bgf_message_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_bgf_message_t(bgf_message_t* instance, bgf_message_t value) {
    *instance = value;
    return true;
}


/**
 * Check the value of light_status_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_light_status_t(light_status_t value){
    return true;
}
  
/**
 * Set the value of light_status_t.
 *
 * \param[out] instance An instance of light_status_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_light_status_t(light_status_t* instance, light_status_t value) {
    *instance = value;
    return true;
}


/**
 * Check the value of light_state_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_light_state_t(light_state_t value){
    return true;
}
  
/**
 * Set the value of light_state_t.
 *
 * \param[out] instance An instance of light_state_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_light_state_t(light_state_t* instance, light_state_t value) {
    *instance = value;
    return true;
}


/**
 * Check the value of indicator_state_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_indicator_state_t(indicator_state_t value){
    return true;
}
  
/**
 * Set the value of indicator_state_t.
 *
 * \param[out] instance An instance of indicator_state_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_indicator_state_t(indicator_state_t* instance, indicator_state_t value) {
    *instance = value;
    return true;
}


/**
 * Check the value of windscreen_wipers_state_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_windscreen_wipers_state_t(windscreen_wipers_state_t value){
    return true;
}
  
/**
 * Set the value of windscreen_wipers_state_t.
 *
 * \param[out] instance An instance of windscreen_wipers_state_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_windscreen_wipers_state_t(windscreen_wipers_state_t* instance, windscreen_wipers_state_t value) {
    *instance = value;
    return true;
}


// Struct getter and setter

/**
 * Get kilometer field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return kilometer_t : Return the value of the got field.
 */
kilometer_t get_kilometer_from_mux_frame_t(mux_frame_t instance) {
    return instance.kilometer;
}
/**
 * Set kilometer field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_kilometer_in_mux_frame_t(mux_frame_t* instance, kilometer_t value) {
    return set_kilometer_t(&instance->kilometer, value);
}

/**
 * Get rpm field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return rpm_t : Return the value of the got field.
 */
rpm_t get_rpm_from_mux_frame_t(mux_frame_t instance) {
    return instance.rpm;
}
/**
 * Set rpm field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_rpm_in_mux_frame_t(mux_frame_t* instance, rpm_t value) {
    return set_rpm_t(&instance->rpm, value);
}

/**
 * Get fuel_level field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return fuel_t : Return the value of the got field.
 */
fuel_t get_fuel_level_from_mux_frame_t(mux_frame_t instance) {
    return instance.fuel_level;
}
/**
 * Set fuel_level field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_fuel_level_in_mux_frame_t(mux_frame_t* instance, fuel_t value) {
    return set_fuel_t(&instance->fuel_level, value);
}

/**
 * Get frame_number field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return mux_frame_number_t : Return the value of the got field.
 */
mux_frame_number_t get_frame_number_from_mux_frame_t(mux_frame_t instance) {
    return instance.frame_number;
}
/**
 * Set frame_number field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_frame_number_in_mux_frame_t(mux_frame_t* instance, mux_frame_number_t value) {
    return set_mux_frame_number_t(&instance->frame_number, value);
}

/**
 * Get speed field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return speed_t : Return the value of the got field.
 */
speed_t get_speed_from_mux_frame_t(mux_frame_t instance) {
    return instance.speed;
}
/**
 * Set speed field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_speed_in_mux_frame_t(mux_frame_t* instance, speed_t value) {
    return set_speed_t(&instance->speed, value);
}

/**
 * Get chassis_issue field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return chassis_issues_t : Return the value of the got field.
 */
chassis_issues_t get_chassis_issue_from_mux_frame_t(mux_frame_t instance) {
    return instance.chassis_issue;
}
/**
 * Set chassis_issue field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_chassis_issue_in_mux_frame_t(mux_frame_t* instance, chassis_issues_t value) {
    return set_chassis_issues_t(&instance->chassis_issue, value);
}

/**
 * Get engine_issue field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return engine_issues_t : Return the value of the got field.
 */
engine_issues_t get_engine_issue_from_mux_frame_t(mux_frame_t instance) {
    return instance.engine_issue;
}
/**
 * Set engine_issue field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_engine_issue_in_mux_frame_t(mux_frame_t* instance, engine_issues_t value) {
    return set_engine_issues_t(&instance->engine_issue, value);
}

/**
 * Get battery_issue field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return battery_issues_t : Return the value of the got field.
 */
battery_issues_t get_battery_issue_from_mux_frame_t(mux_frame_t instance) {
    return instance.battery_issue;
}
/**
 * Set battery_issue field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_battery_issue_in_mux_frame_t(mux_frame_t* instance, battery_issues_t value) {
    return set_battery_issues_t(&instance->battery_issue, value);
}

/**
 * Get crc8 field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return crc8_t : Return the value of the got field.
 */
crc8_t get_crc8_from_mux_frame_t(mux_frame_t instance) {
    return instance.crc8;
}
/**
 * Set crc8 field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_crc8_in_mux_frame_t(mux_frame_t* instance, crc8_t value) {
    return set_crc8_t(&instance->crc8, value);
}

/**
 * Check all values to set in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_mux_frame_t(kilometer_t kilometer, rpm_t rpm, fuel_t fuel_level, mux_frame_number_t frame_number, speed_t speed, chassis_issues_t chassis_issue, engine_issues_t engine_issue, battery_issues_t battery_issue, crc8_t crc8) {
    if (!check_kilometer_t(kilometer)) { return false;}
    if (!check_rpm_t(rpm)) { return false;}
    if (!check_fuel_t(fuel_level)) { return false;}
    if (!check_mux_frame_number_t(frame_number)) { return false;}
    if (!check_speed_t(speed)) { return false;}
    if (!check_chassis_issues_t(chassis_issue)) { return false;}
    if (!check_engine_issues_t(engine_issue)) { return false;}
    if (!check_battery_issues_t(battery_issue)) { return false;}
    if (!check_crc8_t(crc8)) { return false;}
    return true;
}


/**
 * Set all field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_mux_frame_t(mux_frame_t* instance, kilometer_t kilometer, rpm_t rpm, fuel_t fuel_level, mux_frame_number_t frame_number, speed_t speed, chassis_issues_t chassis_issue, engine_issues_t engine_issue, battery_issues_t battery_issue, crc8_t crc8) {
    if (!check_mux_frame_t(kilometer, rpm, fuel_level, frame_number, speed, chassis_issue, engine_issue, battery_issue, crc8)) {
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




/**
 * Get kilometer field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return kilometer_t : Return the value of the got field.
 */
kilometer_t get_kilometer_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.kilometer;
}
/**
 * Set kilometer field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_kilometer_in_bcgv_frame_t(bcgv_frame_t* instance, kilometer_t value) {
    return set_kilometer_t(&instance->kilometer, value);
}

/**
 * Get rpm field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return rpm_dashboard_t : Return the value of the got field.
 */
rpm_dashboard_t get_rpm_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.rpm;
}
/**
 * Set rpm field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_rpm_in_bcgv_frame_t(bcgv_frame_t* instance, rpm_dashboard_t value) {
    return set_rpm_dashboard_t(&instance->rpm, value);
}

/**
 * Get speed field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return speed_t : Return the value of the got field.
 */
speed_t get_speed_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.speed;
}
/**
 * Set speed field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_speed_in_bcgv_frame_t(bcgv_frame_t* instance, speed_t value) {
    return set_speed_t(&instance->speed, value);
}

/**
 * Get fuel_percent_level field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return fuel_t : Return the value of the got field.
 */
fuel_t get_fuel_percent_level_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.fuel_percent_level;
}
/**
 * Set fuel_percent_level field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_fuel_percent_level_in_bcgv_frame_t(bcgv_frame_t* instance, fuel_t value) {
    return set_fuel_t(&instance->fuel_percent_level, value);
}

/**
 * Get dashboard_light field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return dashboard_light_t : Return the value of the got field.
 */
dashboard_light_t get_dashboard_light_from_bcgv_frame_t(bcgv_frame_t instance) {
    return instance.dashboard_light;
}
/**
 * Set dashboard_light field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_dashboard_light_in_bcgv_frame_t(bcgv_frame_t* instance, dashboard_light_t value) {
    return set_dashboard_light_t(&instance->dashboard_light, value);
}

/**
 * Check all values to set in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_bcgv_frame_t(kilometer_t kilometer, rpm_dashboard_t rpm, speed_t speed, fuel_t fuel_percent_level, dashboard_light_t dashboard_light) {
    if (!check_kilometer_t(kilometer)) { return false;}
    if (!check_rpm_dashboard_t(rpm)) { return false;}
    if (!check_speed_t(speed)) { return false;}
    if (!check_fuel_t(fuel_percent_level)) { return false;}
    if (!check_dashboard_light_t(dashboard_light)) { return false;}
    return true;
}


/**
 * Set all field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_bcgv_frame_t(bcgv_frame_t* instance, kilometer_t kilometer, rpm_dashboard_t rpm, speed_t speed, fuel_t fuel_percent_level, dashboard_light_t dashboard_light) {
    if (!check_bcgv_frame_t(kilometer, rpm, speed, fuel_percent_level, dashboard_light)) {
        return false;
    }
    set_kilometer_in_bcgv_frame_t(instance, kilometer);
    set_rpm_in_bcgv_frame_t(instance, rpm);
    set_speed_in_bcgv_frame_t(instance, speed);
    set_fuel_percent_level_in_bcgv_frame_t(instance, fuel_percent_level);
    set_dashboard_light_in_bcgv_frame_t(instance, dashboard_light);
    return true;
}




