#ifndef DATA_MANAGEMENT_H
#define DATA_MANAGEMENT_H

#include <stdint.h>

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


typedef uint16_t bgf_trame_t;
typedef uint32_t kilometer_t;
typedef uint32_t rpm_t;
typedef uint16_t rpm_dashboard_t;
typedef uint8_t fuel_t;
typedef uint8_t fuel_percent_t;
typedef uint8_t mux_frame_number_t;
typedef uint8_t speed_t;
typedef uint8_t crc8_t;
typedef uint8_t comodo_frame_t;
typedef uint16_t dashboard_light_t;


typedef enum chassis_issues_t_struct {
    NOTHING_CHASSIS = 0,
    TIRES_PRESSURE = 1,
    BRAKE_FAILURE = 2,
} chassis_issues_t;

typedef enum engine_issues_t_struct {
    NOTHING_ENGINE = 0,
    PRESSURE_FAULT = 1,
    COOLANT_TEMPERATURE = 2,
    OIL_OVERHEATING = 3,
} engine_issues_t;

typedef enum battery_issues_t_struct {
    NOTHING_BATTERY = 0,
    UNLOADED = 1,
    OUTAGE = 2,
} battery_issues_t;

typedef enum bgf_message_t_struct {
    POSITION_LIGHT = 0,
    LOW_BEAM = 1,
    HIGH_BEAM = 2,
    RIGHT_INDICATOR = 3,
    LEFT_INDICATOR = 4,
} bgf_message_t;

typedef enum light_status_t_struct {
    OFF = 0,
    ON = 1,
} light_status_t;

typedef enum light_state_t_struct {
    LIGHT_OFF = 0,
    LIGHT_ON = 1,
    LIGHT_ERROR = 2,
    LIGHT_ACQUITTED = 3,
} light_state_t;

typedef enum indicator_state_t_struct {
    INDICATOR_OFF = 0,
    ACTIVATED_OFF = 1,
    ACTIVATED_ON = 2,
    INDICATOR_ERROR = 3,
    INDICATOR_ACQUITTED = 4,
} indicator_state_t;

typedef enum windscreen_wipers_state_t_struct {
    ALL_OFF = 0,
    WIPERS_ACTIVATED = 1,
    WDSCRN_CLN_WPRS_ACTIVATED = 2,
    TMR_WPRS_WDSCRN_CLN_OFF = 3,
} windscreen_wipers_state_t;

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

typedef struct {
    kilometer_t kilometer;
    rpm_dashboard_t rpm;
    speed_t speed;
    fuel_t fuel_percent_level;
    dashboard_light_t dashboard_light;
} bcgv_frame_t;

#endif
