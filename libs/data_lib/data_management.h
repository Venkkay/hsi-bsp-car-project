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


/**
 * Atomic type bgf_trame_t.
 *
 * \details READ / WRITE 
*/
typedef uint16_t bgf_trame_t;
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
 * \details Use to describe de chassis issue 
*/
typedef enum chassis_issues_t_struct {
    NOTHING_CHASSIS = 0,
    TIRES_PRESSURE = 1,
    BRAKE_FAILURE = 2,
} chassis_issues_t;

/**
 * Enum engine_issues_t.
 *
 * \details Use to describe to engine's issue 
*/
typedef enum engine_issues_t_struct {
    NOTHING_ENGINE = 0,
    PRESSURE_FAULT = 1,
    COOLANT_TEMPERATURE = 2,
    OIL_OVERHEATING = 3,
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
    POSITION_LIGHT = 0,
    LOW_BEAM = 1,
    HIGH_BEAM = 2,
    RIGHT_INDICATOR = 3,
    LEFT_INDICATOR = 4,
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
    LIGHT_OFF = 0,
    LIGHT_ON = 1,
    LIGHT_ERROR = 2,
    LIGHT_ACQUITTED = 3,
} light_state_t;

/**
 * Enum indicator_state_t.
 *
 * \details Describe the possible states of indicators and warnings 
*/
typedef enum indicator_state_t_struct {
    INDICATOR_OFF = 0,
    ACTIVATED_OFF = 1,
    ACTIVATED_ON = 2,
    INDICATOR_ERROR = 3,
    INDICATOR_ACQUITTED = 4,
} indicator_state_t;

/**
 * Enum windscreen_wipers_state_t.
 *
 * \details Describe the possible states of the wipers and the windscreen washer 
*/
typedef enum windscreen_wipers_state_t_struct {
    ALL_OFF = 0,
    WIPERS_ACTIVATED = 1,
    WDSCRN_CLN_WPRS_ACTIVATED = 2,
    TMR_WPRS_WDSCRN_CLN_OFF = 3,
} windscreen_wipers_state_t;

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
    fuel_t fuel_percent_level;
    dashboard_light_t dashboard_light;
} bcgv_frame_t;

// Function signatures
// Atomic types setter
bool check_bgf_trame_t(uint16_t value);
bool set_bgf_trame_t(bgf_trame_t* instance, uint16_t value);
bool check_kilometer_t(uint32_t value);
bool set_kilometer_t(kilometer_t* instance, uint32_t value);
bool check_rpm_t(uint32_t value);
bool set_rpm_t(rpm_t* instance, uint32_t value);
bool check_rpm_dashboard_t(uint16_t value);
bool set_rpm_dashboard_t(rpm_dashboard_t* instance, uint16_t value);
bool check_fuel_t(uint8_t value);
bool set_fuel_t(fuel_t* instance, uint8_t value);
bool check_fuel_percent_t(uint8_t value);
bool set_fuel_percent_t(fuel_percent_t* instance, uint8_t value);
bool check_mux_frame_number_t(uint8_t value);
bool set_mux_frame_number_t(mux_frame_number_t* instance, uint8_t value);
bool check_speed_t(uint8_t value);
bool set_speed_t(speed_t* instance, uint8_t value);
bool check_crc8_t(uint8_t value);
bool set_crc8_t(crc8_t* instance, uint8_t value);

// Flags getter and setter
uint8_t get_cmd_warning_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_warning_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint8_t get_cmd_position_light_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_position_light_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint8_t get_cmd_low_beam_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_low_beam_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint8_t get_cmd_high_beam_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_high_beam_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint8_t get_cmd_right_indicator_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_right_indicator_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint8_t get_cmd_left_indicator_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_left_indicator_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint8_t get_cmd_wipers_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_wipers_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint8_t get_cmd_washer_from_comodo_frame_t(comodo_frame_t instance);
bool set_cmd_washer_in_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
bool set_all_flag_comodo_frame_t(comodo_frame_t* instance, uint8_t cmd_warning, uint8_t cmd_position_light, uint8_t cmd_low_beam, uint8_t cmd_high_beam, uint8_t cmd_right_indicator, uint8_t cmd_left_indicator, uint8_t cmd_wipers, uint8_t cmd_washer);
bool check_comodo_frame_t(uint8_t value);
bool set_comodo_frame_t(comodo_frame_t* instance, uint8_t value);
uint16_t get_position_light_from_dashboard_light_t(dashboard_light_t instance);
bool set_position_light_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_low_beam_from_dashboard_light_t(dashboard_light_t instance);
bool set_low_beam_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_high_beam_from_dashboard_light_t(dashboard_light_t instance);
bool set_high_beam_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_fuel_from_dashboard_light_t(dashboard_light_t instance);
bool set_fuel_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_motor_issue_from_dashboard_light_t(dashboard_light_t instance);
bool set_motor_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_pressure_issue_from_dashboard_light_t(dashboard_light_t instance);
bool set_pressure_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_unused_from_dashboard_light_t(dashboard_light_t instance);
bool set_unused_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_discharged_battery_from_dashboard_light_t(dashboard_light_t instance);
bool set_discharged_battery_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_warning_from_dashboard_light_t(dashboard_light_t instance);
bool set_warning_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_battery_issue_from_dashboard_light_t(dashboard_light_t instance);
bool set_battery_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_coolant_temperature_from_dashboard_light_t(dashboard_light_t instance);
bool set_coolant_temperature_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_motor_pressure_from_dashboard_light_t(dashboard_light_t instance);
bool set_motor_pressure_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_oil_overheat_from_dashboard_light_t(dashboard_light_t instance);
bool set_oil_overheat_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_brake_issue_from_dashboard_light_t(dashboard_light_t instance);
bool set_brake_issue_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_wiper_active_from_dashboard_light_t(dashboard_light_t instance);
bool set_wiper_active_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
uint16_t get_washer_active_from_dashboard_light_t(dashboard_light_t instance);
bool set_washer_active_in_dashboard_light_t(dashboard_light_t* instance, uint16_t value);
bool set_all_flag_dashboard_light_t(dashboard_light_t* instance, uint16_t position_light, uint16_t low_beam, uint16_t high_beam, uint16_t fuel, uint16_t motor_issue, uint16_t pressure_issue, uint16_t unused, uint16_t discharged_battery, uint16_t warning, uint16_t battery_issue, uint16_t coolant_temperature, uint16_t motor_pressure, uint16_t oil_overheat, uint16_t brake_issue, uint16_t wiper_active, uint16_t washer_active);
bool check_dashboard_light_t(uint16_t value);
bool set_dashboard_light_t(dashboard_light_t* instance, uint16_t value);

// Enums getter and setter
bool check_chassis_issues_t(chassis_issues_t value);
bool set_chassis_issues_t(chassis_issues_t* instance, chassis_issues_t value);
bool check_engine_issues_t(engine_issues_t value);
bool set_engine_issues_t(engine_issues_t* instance, engine_issues_t value);
bool check_battery_issues_t(battery_issues_t value);
bool set_battery_issues_t(battery_issues_t* instance, battery_issues_t value);
bool check_bgf_message_t(bgf_message_t value);
bool set_bgf_message_t(bgf_message_t* instance, bgf_message_t value);
bool check_light_status_t(light_status_t value);
bool set_light_status_t(light_status_t* instance, light_status_t value);
bool check_light_state_t(light_state_t value);
bool set_light_state_t(light_state_t* instance, light_state_t value);
bool check_indicator_state_t(indicator_state_t value);
bool set_indicator_state_t(indicator_state_t* instance, indicator_state_t value);
bool check_windscreen_wipers_state_t(windscreen_wipers_state_t value);
bool set_windscreen_wipers_state_t(windscreen_wipers_state_t* instance, windscreen_wipers_state_t value);

// Struct getter and setter
kilometer_t get_kilometer_from_mux_frame_t(mux_frame_t instance);
bool set_kilometer_in_mux_frame_t(mux_frame_t* instance, kilometer_t value);
rpm_t get_rpm_from_mux_frame_t(mux_frame_t instance);
bool set_rpm_in_mux_frame_t(mux_frame_t* instance, rpm_t value);
fuel_t get_fuel_level_from_mux_frame_t(mux_frame_t instance);
bool set_fuel_level_in_mux_frame_t(mux_frame_t* instance, fuel_t value);
mux_frame_number_t get_frame_number_from_mux_frame_t(mux_frame_t instance);
bool set_frame_number_in_mux_frame_t(mux_frame_t* instance, mux_frame_number_t value);
speed_t get_speed_from_mux_frame_t(mux_frame_t instance);
bool set_speed_in_mux_frame_t(mux_frame_t* instance, speed_t value);
chassis_issues_t get_chassis_issue_from_mux_frame_t(mux_frame_t instance);
bool set_chassis_issue_in_mux_frame_t(mux_frame_t* instance, chassis_issues_t value);
engine_issues_t get_engine_issue_from_mux_frame_t(mux_frame_t instance);
bool set_engine_issue_in_mux_frame_t(mux_frame_t* instance, engine_issues_t value);
battery_issues_t get_battery_issue_from_mux_frame_t(mux_frame_t instance);
bool set_battery_issue_in_mux_frame_t(mux_frame_t* instance, battery_issues_t value);
crc8_t get_crc8_from_mux_frame_t(mux_frame_t instance);
bool set_crc8_in_mux_frame_t(mux_frame_t* instance, crc8_t value);
bool check_mux_frame_t(kilometer_t kilometer, rpm_t rpm, fuel_t fuel_level, mux_frame_number_t frame_number, speed_t speed, chassis_issues_t chassis_issue, engine_issues_t engine_issue, battery_issues_t battery_issue, crc8_t crc8);
bool set_mux_frame_t(mux_frame_t* instance, kilometer_t kilometer, rpm_t rpm, fuel_t fuel_level, mux_frame_number_t frame_number, speed_t speed, chassis_issues_t chassis_issue, engine_issues_t engine_issue, battery_issues_t battery_issue, crc8_t crc8);
kilometer_t get_kilometer_from_bcgv_frame_t(bcgv_frame_t instance);
bool set_kilometer_in_bcgv_frame_t(bcgv_frame_t* instance, kilometer_t value);
rpm_dashboard_t get_rpm_from_bcgv_frame_t(bcgv_frame_t instance);
bool set_rpm_in_bcgv_frame_t(bcgv_frame_t* instance, rpm_dashboard_t value);
speed_t get_speed_from_bcgv_frame_t(bcgv_frame_t instance);
bool set_speed_in_bcgv_frame_t(bcgv_frame_t* instance, speed_t value);
fuel_t get_fuel_percent_level_from_bcgv_frame_t(bcgv_frame_t instance);
bool set_fuel_percent_level_in_bcgv_frame_t(bcgv_frame_t* instance, fuel_t value);
dashboard_light_t get_dashboard_light_from_bcgv_frame_t(bcgv_frame_t instance);
bool set_dashboard_light_in_bcgv_frame_t(bcgv_frame_t* instance, dashboard_light_t value);
bool check_bcgv_frame_t(kilometer_t kilometer, rpm_dashboard_t rpm, speed_t speed, fuel_t fuel_percent_level, dashboard_light_t dashboard_light);
bool set_bcgv_frame_t(bcgv_frame_t* instance, kilometer_t kilometer, rpm_dashboard_t rpm, speed_t speed, fuel_t fuel_percent_level, dashboard_light_t dashboard_light);
#endif
