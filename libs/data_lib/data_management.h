/**
 * \file	data_management.h
 * \brief	Header file of the data management lib with the types, enums, structs and functions declarations.
 * \author	data_lib_generator tool
 */

#ifndef DATA_MANAGEMENT_H
#define DATA_MANAGEMENT_H

#include <stdint.h>
#include <stdbool.h>

#define MIN_RPM 0
#define MAX_RPM 10000
#define MIN_RPM_DASHBOARD 0
#define MAX_RPM_DASHBOARD 1000
#define MIN_FUEL 0
#define MAX_FUEL 40
#define MIN_FUEL_PERCENT 0
#define MAX_FUEL_PERCENT 100
#define MIN_MUX_FRAME_NUMBER 1
#define MAX_MUX_FRAME_NUMBER 100
#define MIN_SPEED 0
#define MAX_SPEED 255
#define SERIAL_BGF 11
#define SERIAL_COM 12


/**
 * Atomic type bgf_frame_t.
 *
 * \details READ / WRITE 
*/
typedef uint16_t bgf_frame_t;
/**
 * Atomic type kilometer_t.
 *
 * \details  
*/
typedef uint32_t kilometer_t;
/**
 * Atomic type rpm_t.
 *
 * \details  
*/
typedef uint32_t rpm_t;
/**
 * Atomic type rpm_dashboard_t.
 *
 * \details For dashboard only 
*/
typedef uint16_t rpm_dashboard_t;
/**
 * Atomic type fuel_t.
 *
 * \details  
*/
typedef uint8_t fuel_t;
/**
 * Atomic type fuel_percent_t.
 *
 * \details For dashboard only 
*/
typedef uint8_t fuel_percent_t;
/**
 * Atomic type mux_frame_number_t.
 *
 * \details Reset to 1 if > 100 
*/
typedef uint8_t mux_frame_number_t;
/**
 * Atomic type speed_t.
 *
 * \details  
*/
typedef uint8_t speed_t;
/**
 * Atomic type crc8_t.
 *
 * \details CRC8 
*/
typedef uint8_t crc8_t;


/**
 * Flag comodo_frame_t.
 *
 * \details READ ONLY
Type to describe the frame sent by the comodo to the BCGV 
*/
typedef uint8_t comodo_frame_t;
/**
 * Flag dashboard_light_t.
 *
 * \details Each piece of information is 1 bit long:
warning
position_light
low_beam
high_beam
tire_pressure
brake_issue
engine_issue
engine_pressure
cooling
oil_overheat
fuel_light
low_battery
dead_battery
useless

wipers
windscreen_washer 
*/
typedef uint16_t dashboard_light_t;


/**
 * Enum chassis_issues_t.
 *
 * \details Use to describe the chassis issue 
*/
typedef enum chassis_issues_t_struct {
    NOTHING_CHASSIS = 0,
    TIRES_PRESSURE = 1,
    BRAKE_FAILURE = 2,
} chassis_issues_t;

/**
 * Enum engine_issues_t.
 *
 * \details Use to describe the engine's issue 
*/
typedef enum engine_issues_t_struct {
    NOTHING_ENGINE = 0,
    PRESSURE_FAULT = 1,
    COOLANT_TEMPERATURE = 2,
    OIL_OVERHEATING = 4,
} engine_issues_t;

/**
 * Enum battery_issues_t.
 *
 * \details Use to describe the battery's issue 
*/
typedef enum battery_issues_t_struct {
    NOTHING_BATTERY = 0,
    UNLOADED = 1,
    OUTAGE = 2,
} battery_issues_t;

/**
 * Enum bgf_message_t.
 *
 * \details Use to define the type of message to be sent and received from the BGF. 
*/
typedef enum bgf_message_t_struct {
    POSITION_LIGHT = 1,
    LOW_BEAM = 2,
    HIGH_BEAM = 3,
    RIGHT_INDICATOR = 4,
    LEFT_INDICATOR = 5,
} bgf_message_t;

/**
 * Enum light_status_t.
 *
 * \details Use to define and find out the status of the element concerned according to the BGF message type.
Use to define the status of the light on the dashboard according to the information from the issues or information. 
*/
typedef enum light_status_t_struct {
    OFF = 0,
    ON = 1,
} light_status_t;

/**
 * Enum light_state_t.
 *
 * \details Describe the possible states of the lights (positions, low, high) 
*/
typedef enum light_state_t_struct {
    ST_LIGHT_OFF = 0,
    ST_LIGHT_ON = 1,
    ST_LIGHT_ERROR = 2,
    ST_LIGHT_ACQUITTED = 3,
} light_state_t;

/**
 * Enum light_event_t.
 *
 * \details Describe the possible events of the lights (positions, low, high) 
*/
typedef enum light_event_t_struct {
    EV_LIGHT_CMD_0 = 0,
    EV_LIGHT_CMD_1 = 1,
    EV_LIGHT_ACK_RCV = 2,
    EV_LIGHT_ACK_NRCV = 3,
} light_event_t;

/**
 * Enum indicator_state_t.
 *
 * \details Describe the possible states of indicators and warnings 
*/
typedef enum indicator_state_t_struct {
    ST_INDICATOR_OFF = 0,
    ST_INDICATOR_ACTIVATED_OFF = 1,
    ST_INDICATOR_ACTIVATED_ON = 2,
    ST_INDICATOR_ERROR = 3,
    ST_INDICATOR_ACQUITTED_OFF = 4,
    ST_INDICATOR_ACQUITTED_ON = 5,
} indicator_state_t;

/**
 * Enum indicator_event_t.
 *
 * \details Describe the possible events of indicators and warnings 
*/
typedef enum indicator_event_t_struct {
    EV_INDICATOR_CMD_0 = 0,
    EV_INDICATOR_CMD_1 = 1,
    EV_INDICATOR_ACK_RCV = 2,
    EV_INDICATOR_ACK_NRCV = 3,
    EV_INDICATOR_TMR_EQ_1 = 4,
    EV_INDICATOR_ERROR = 5,
} indicator_event_t;

/**
 * Enum wipers_washer_state_t.
 *
 * \details Describe the possible states of wipers and the windscreen washer 
*/
typedef enum wipers_washer_state_t_struct {
    ST_WP_WS_ALL_OFF = 0,
    ST_WP_ACTIVATED = 1,
    ST_WP_WS_ON = 2,
    ST_TMR_WP_WS_OFF = 3,
} wipers_washer_state_t;

/**
 * Enum wipers_washer_event_t.
 *
 * \details Describe the possible events of wipers and the windscreen washer 
*/
typedef enum wipers_washer_event_t_struct {
    EV_WP_WS_CMD_WP_0_CMD_WS_0 = 0,
    EV_WP_WS_CMD_WP_0 = 1,
    EV_WP_WS_CMD_WP_1 = 2,
    EV_WP_WS_CMD_WS_0 = 3,
    EV_WP_WS_CMD_WS_1 = 4,
    EV_WP_WS_TMR_GT2 = 5,
    EV_WP_WS_TMR_LT2 = 6,
    EV_WP_WS_ERROR = 7,
} wipers_washer_event_t;



/**
 * Struct type mux_frame_t.
 *
 * \details READ ONLY 
*/
typedef struct {
    kilometer_t kilometer;
    rpm_t rpm;
    fuel_t fuel_level;
    mux_frame_number_t frame_number;
    speed_t speed;
    chassis_issues_t chassis_issue;
    engine_issues_t engine_issue;
    battery_issues_t battery_issue;
    crc8_t crc8;
} mux_frame_t;

/**
 * Struct type bcgv_frame_t.
 *
 * \details WRITE ONLY 
*/
typedef struct {
    kilometer_t kilometer;
    rpm_dashboard_t rpm;
    speed_t speed;
    fuel_percent_t fuel_percent_level;
    dashboard_light_t dashboard_light;
} bcgv_frame_t;

// Function signatures
// Atomic types setter
/**
 * Set the value of bgf_frame_t.
 *
 * \param[out] instance : An instance of bgf_frame_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_bgf_frame_t(bgf_frame_t* instance, const uint16_t value);
/**
 * Set the value of kilometer_t.
 *
 * \param[out] instance : An instance of kilometer_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_kilometer_t(kilometer_t* instance, const uint32_t value);
/**
 * Check the value of rpm_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_rpm_t(const uint32_t value);
/**
 * Set the value of rpm_t.
 *
 * \param[out] instance : An instance of rpm_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_rpm_t(rpm_t* instance, const uint32_t value);
/**
 * Check the value of rpm_dashboard_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_rpm_dashboard_t(const uint16_t value);
/**
 * Set the value of rpm_dashboard_t.
 *
 * \param[out] instance : An instance of rpm_dashboard_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_rpm_dashboard_t(rpm_dashboard_t* instance, const uint16_t value);
/**
 * Check the value of fuel_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_fuel_t(const uint8_t value);
/**
 * Set the value of fuel_t.
 *
 * \param[out] instance : An instance of fuel_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_fuel_t(fuel_t* instance, const uint8_t value);
/**
 * Check the value of fuel_percent_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_fuel_percent_t(const uint8_t value);
/**
 * Set the value of fuel_percent_t.
 *
 * \param[out] instance : An instance of fuel_percent_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_fuel_percent_t(fuel_percent_t* instance, const uint8_t value);
/**
 * Check the value of mux_frame_number_t.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_mux_frame_number_t(const uint8_t value);
/**
 * Set the value of mux_frame_number_t.
 *
 * \param[out] instance : An instance of mux_frame_number_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_mux_frame_number_t(mux_frame_number_t* instance, const uint8_t value);
/**
 * Set the value of speed_t.
 *
 * \param[out] instance : An instance of speed_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_speed_t(speed_t* instance, const uint8_t value);
/**
 * Set the value of crc8_t.
 *
 * \param[out] instance : An instance of crc8_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is set, False otherwise.
 */
bool set_crc8_t(crc8_t* instance, const uint8_t value);

// Flags getter and setter
/**
 * Get cmd_warning flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_warning_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_warning.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_warning_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_warning flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_warning_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get cmd_position_light flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_position_light_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_position_light.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_position_light_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_position_light flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_position_light_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get cmd_low_beam flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_low_beam_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_low_beam.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_low_beam_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_low_beam flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_low_beam_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get cmd_high_beam flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_high_beam_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_high_beam.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_high_beam_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_high_beam flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_high_beam_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get cmd_right_indicator flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_right_indicator_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_right_indicator.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_right_indicator_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_right_indicator flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_right_indicator_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get cmd_left_indicator flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_left_indicator_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_left_indicator.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_left_indicator_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_left_indicator flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_left_indicator_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get cmd_wipers flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_wipers_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_wipers.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_wipers_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_wipers flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_wipers_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get cmd_washer flag from comodo_frame_t.
 *
 * @param[in] instance An instance of comodo_frame_t.
 * @return uint8_t : Return the value of the got flag.
 */
uint8_t get_cmd_washer_from_comodo_frame_t(const comodo_frame_t instance);
/**
 * Check the value of cmd_washer.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_cmd_washer_in_comodo_frame_t(const uint8_t value);
/**
 * Set cmd_washer flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_cmd_washer_in_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Set all flag in comodo_frame_t.
 *
 * @param[out] instance An instance of comodo_frame_t.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_all_flag_comodo_frame_t(comodo_frame_t* instance, const uint8_t cmd_warning, const uint8_t cmd_position_light, const uint8_t cmd_low_beam, const uint8_t cmd_high_beam, const uint8_t cmd_right_indicator, const uint8_t cmd_left_indicator, const uint8_t cmd_wipers, const uint8_t cmd_washer);
/**
 * Set comodo_frame_t.
 *
 * \param[out] instance An instance of comodo_frame_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_comodo_frame_t(comodo_frame_t* instance, const uint8_t value);
/**
 * Get position_light flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_position_light_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of position_light.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_position_light_in_dashboard_light_t(const uint16_t value);
/**
 * Set position_light flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_position_light_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get low_beam flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_low_beam_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of low_beam.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_low_beam_in_dashboard_light_t(const uint16_t value);
/**
 * Set low_beam flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_low_beam_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get high_beam flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_high_beam_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of high_beam.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_high_beam_in_dashboard_light_t(const uint16_t value);
/**
 * Set high_beam flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_high_beam_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get fuel flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_fuel_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of fuel.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_fuel_in_dashboard_light_t(const uint16_t value);
/**
 * Set fuel flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_fuel_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get motor_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_motor_issue_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of motor_issue.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_motor_issue_in_dashboard_light_t(const uint16_t value);
/**
 * Set motor_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_motor_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get pressure_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_pressure_issue_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of pressure_issue.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_pressure_issue_in_dashboard_light_t(const uint16_t value);
/**
 * Set pressure_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_pressure_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get unused flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_unused_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of unused.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_unused_in_dashboard_light_t(const uint16_t value);
/**
 * Set unused flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_unused_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get discharged_battery flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_discharged_battery_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of discharged_battery.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_discharged_battery_in_dashboard_light_t(const uint16_t value);
/**
 * Set discharged_battery flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_discharged_battery_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get warning flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_warning_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of warning.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_warning_in_dashboard_light_t(const uint16_t value);
/**
 * Set warning flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_warning_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get battery_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_battery_issue_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of battery_issue.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_battery_issue_in_dashboard_light_t(const uint16_t value);
/**
 * Set battery_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_battery_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get coolant_temperature flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_coolant_temperature_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of coolant_temperature.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_coolant_temperature_in_dashboard_light_t(const uint16_t value);
/**
 * Set coolant_temperature flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_coolant_temperature_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get motor_pressure flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_motor_pressure_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of motor_pressure.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_motor_pressure_in_dashboard_light_t(const uint16_t value);
/**
 * Set motor_pressure flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_motor_pressure_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get oil_overheat flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_oil_overheat_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of oil_overheat.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_oil_overheat_in_dashboard_light_t(const uint16_t value);
/**
 * Set oil_overheat flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_oil_overheat_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get brake_issue flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_brake_issue_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of brake_issue.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_brake_issue_in_dashboard_light_t(const uint16_t value);
/**
 * Set brake_issue flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_brake_issue_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get wiper_active flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_wiper_active_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of wiper_active.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_wiper_active_in_dashboard_light_t(const uint16_t value);
/**
 * Set wiper_active flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_wiper_active_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Get washer_active flag from dashboard_light_t.
 *
 * @param[in] instance An instance of dashboard_light_t.
 * @return uint16_t : Return the value of the got flag.
 */
uint16_t get_washer_active_from_dashboard_light_t(const dashboard_light_t instance);
/**
 * Check the value of washer_active.
 *
 * \param[in] value : The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_washer_active_in_dashboard_light_t(const uint16_t value);
/**
 * Set washer_active flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_washer_active_in_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);
/**
 * Set all flag in dashboard_light_t.
 *
 * @param[out] instance An instance of dashboard_light_t.
 * @return Return True if the value is valid, False otherwise.
 */
bool set_all_flag_dashboard_light_t(dashboard_light_t* instance, const uint16_t position_light, const uint16_t low_beam, const uint16_t high_beam, const uint16_t fuel, const uint16_t motor_issue, const uint16_t pressure_issue, const uint16_t unused, const uint16_t discharged_battery, const uint16_t warning, const uint16_t battery_issue, const uint16_t coolant_temperature, const uint16_t motor_pressure, const uint16_t oil_overheat, const uint16_t brake_issue, const uint16_t wiper_active, const uint16_t washer_active);
/**
 * Set dashboard_light_t.
 *
 * \param[out] instance An instance of dashboard_light_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_dashboard_light_t(dashboard_light_t* instance, const uint16_t value);

// Enums getter and setter
/**
 * Check the value of chassis_issues_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_chassis_issues_t(uint8_t value);
/**
 * Set the value of chassis_issues_t.
 *
 * \param[out] instance An instance of chassis_issues_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_chassis_issues_t(chassis_issues_t* instance, uint8_t value);
/**
 * Check the value of engine_issues_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_engine_issues_t(uint8_t value);
/**
 * Set the value of engine_issues_t.
 *
 * \param[out] instance An instance of engine_issues_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_engine_issues_t(engine_issues_t* instance, uint8_t value);
/**
 * Check the value of battery_issues_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_battery_issues_t(uint8_t value);
/**
 * Set the value of battery_issues_t.
 *
 * \param[out] instance An instance of battery_issues_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_battery_issues_t(battery_issues_t* instance, uint8_t value);
/**
 * Check the value of bgf_message_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_bgf_message_t(uint8_t value);
/**
 * Set the value of bgf_message_t.
 *
 * \param[out] instance An instance of bgf_message_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_bgf_message_t(bgf_message_t* instance, uint8_t value);
/**
 * Check the value of light_status_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_light_status_t(uint8_t value);
/**
 * Set the value of light_status_t.
 *
 * \param[out] instance An instance of light_status_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_light_status_t(light_status_t* instance, uint8_t value);
/**
 * Check the value of light_state_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_light_state_t(uint8_t value);
/**
 * Set the value of light_state_t.
 *
 * \param[out] instance An instance of light_state_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_light_state_t(light_state_t* instance, uint8_t value);
/**
 * Check the value of light_event_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_light_event_t(uint8_t value);
/**
 * Set the value of light_event_t.
 *
 * \param[out] instance An instance of light_event_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_light_event_t(light_event_t* instance, uint8_t value);
/**
 * Check the value of indicator_state_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_indicator_state_t(uint8_t value);
/**
 * Set the value of indicator_state_t.
 *
 * \param[out] instance An instance of indicator_state_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_indicator_state_t(indicator_state_t* instance, uint8_t value);
/**
 * Check the value of indicator_event_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_indicator_event_t(uint8_t value);
/**
 * Set the value of indicator_event_t.
 *
 * \param[out] instance An instance of indicator_event_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_indicator_event_t(indicator_event_t* instance, uint8_t value);
/**
 * Check the value of wipers_washer_state_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_wipers_washer_state_t(uint8_t value);
/**
 * Set the value of wipers_washer_state_t.
 *
 * \param[out] instance An instance of wipers_washer_state_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_wipers_washer_state_t(wipers_washer_state_t* instance, uint8_t value);
/**
 * Check the value of wipers_washer_event_t.
 *
 * \param[in] value The value to check.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_wipers_washer_event_t(uint8_t value);
/**
 * Set the value of wipers_washer_event_t.
 *
 * \param[out] instance An instance of wipers_washer_event_t.
 * \param[in] value : The value to set.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_wipers_washer_event_t(wipers_washer_event_t* instance, uint8_t value);

// Struct getter and setter
/**
 * Get kilometer field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return kilometer_t : Return the value of the got field.
 */
kilometer_t get_kilometer_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set kilometer field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_kilometer_in_mux_frame_t(mux_frame_t* instance, const uint32_t value);
/**
 * Get rpm field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return rpm_t : Return the value of the got field.
 */
rpm_t get_rpm_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set rpm field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_rpm_in_mux_frame_t(mux_frame_t* instance, const uint32_t value);
/**
 * Get fuel_level field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return fuel_t : Return the value of the got field.
 */
fuel_t get_fuel_level_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set fuel_level field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_fuel_level_in_mux_frame_t(mux_frame_t* instance, const uint8_t value);
/**
 * Get frame_number field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return mux_frame_number_t : Return the value of the got field.
 */
mux_frame_number_t get_frame_number_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set frame_number field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_frame_number_in_mux_frame_t(mux_frame_t* instance, const uint8_t value);
/**
 * Get speed field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return speed_t : Return the value of the got field.
 */
speed_t get_speed_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set speed field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_speed_in_mux_frame_t(mux_frame_t* instance, const uint8_t value);
/**
 * Get chassis_issue field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return chassis_issues_t : Return the value of the got field.
 */
chassis_issues_t get_chassis_issue_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set chassis_issue field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_chassis_issue_in_mux_frame_t(mux_frame_t* instance, const uint8_t value);
/**
 * Get engine_issue field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return engine_issues_t : Return the value of the got field.
 */
engine_issues_t get_engine_issue_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set engine_issue field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_engine_issue_in_mux_frame_t(mux_frame_t* instance, const uint8_t value);
/**
 * Get battery_issue field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return battery_issues_t : Return the value of the got field.
 */
battery_issues_t get_battery_issue_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set battery_issue field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_battery_issue_in_mux_frame_t(mux_frame_t* instance, const uint8_t value);
/**
 * Get crc8 field from mux_frame_t.
 *
 * \param[in] instance An instance of mux_frame_t.
 * \return crc8_t : Return the value of the got field.
 */
crc8_t get_crc8_from_mux_frame_t(const mux_frame_t instance);
/**
 * Set crc8 field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_crc8_in_mux_frame_t(mux_frame_t* instance, const uint8_t value);
/**
 * Check all values to set in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_mux_frame_t(const rpm_t rpm, const fuel_t fuel_level, const mux_frame_number_t frame_number);
/**
 * Set all field in mux_frame_t.
 *
 * \param[out] instance : An instance of mux_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_mux_frame_t(mux_frame_t* instance, kilometer_t kilometer, rpm_t rpm, fuel_t fuel_level, mux_frame_number_t frame_number, speed_t speed, chassis_issues_t chassis_issue, engine_issues_t engine_issue, battery_issues_t battery_issue, crc8_t crc8);
/**
 * Get kilometer field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return kilometer_t : Return the value of the got field.
 */
kilometer_t get_kilometer_from_bcgv_frame_t(const bcgv_frame_t instance);
/**
 * Set kilometer field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_kilometer_in_bcgv_frame_t(bcgv_frame_t* instance, const uint32_t value);
/**
 * Get rpm field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return rpm_dashboard_t : Return the value of the got field.
 */
rpm_dashboard_t get_rpm_from_bcgv_frame_t(const bcgv_frame_t instance);
/**
 * Set rpm field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_rpm_in_bcgv_frame_t(bcgv_frame_t* instance, const uint16_t value);
/**
 * Get speed field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return speed_t : Return the value of the got field.
 */
speed_t get_speed_from_bcgv_frame_t(const bcgv_frame_t instance);
/**
 * Set speed field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_speed_in_bcgv_frame_t(bcgv_frame_t* instance, const uint8_t value);
/**
 * Get fuel_percent_level field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return fuel_percent_t : Return the value of the got field.
 */
fuel_percent_t get_fuel_percent_level_from_bcgv_frame_t(const bcgv_frame_t instance);
/**
 * Set fuel_percent_level field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_fuel_percent_level_in_bcgv_frame_t(bcgv_frame_t* instance, const uint8_t value);
/**
 * Get dashboard_light field from bcgv_frame_t.
 *
 * \param[in] instance An instance of bcgv_frame_t.
 * \return dashboard_light_t : Return the value of the got field.
 */
dashboard_light_t get_dashboard_light_from_bcgv_frame_t(const bcgv_frame_t instance);
/**
 * Set dashboard_light field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \param[in] value : The value to set.
 * \return bool :  Return True if the value is valid, False otherwise.
 */
bool set_dashboard_light_in_bcgv_frame_t(bcgv_frame_t* instance, const uint16_t value);
/**
 * Check all values to set in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool check_bcgv_frame_t(const rpm_dashboard_t rpm, const fuel_percent_t fuel_percent_level);
/**
 * Set all field in bcgv_frame_t.
 *
 * \param[out] instance : An instance of bcgv_frame_t.
 * \return bool : Return True if the value is valid, False otherwise.
 */
bool set_bcgv_frame_t(bcgv_frame_t* instance, kilometer_t kilometer, rpm_dashboard_t rpm, speed_t speed, fuel_percent_t fuel_percent_level, dashboard_light_t dashboard_light);
/**
 * \brief	Init dashboard_state
 * \return	bcgv_frame_t : the initialized struct.
 */
/**
 * \brief	Init light_state_current
 * \return	light_state_t : the initialized struct.
 */
#endif // DATA_MANAGEMENT_H
