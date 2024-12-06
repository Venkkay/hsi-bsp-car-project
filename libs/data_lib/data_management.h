#ifndef DATA_MANAGEMENT_H
#define DATA_MANAGEMENT_H

#include <stddef.h>

typedef uint8_t comodo_frame_t;
typedef uint16_t bgf_trame_t;
typedef uint32_t kilometer_t;
typedef uint32_t rpm_t;
typedef uint16_t rpm_dashboard_t;
typedef uint8_t fuel_t;
typedef uint8_t fuel_percent_t;
typedef uint8_t mux_frame_number_t;
typedef uint8_t speed_t;
typedef uint16_t dashboard_light_t;


enum chassis_issues_t {
    NOTHING_CHASSIS = 0,
    TIRES_PRESSURE = 1,
    BRAKE_FAILURE = 2,
};

enum engine_issues_t {
    NOTHING_ENGINE = 0,
    PRESSURE_FAULT = 1,
    COOLANT_TEMPERATURE = 2,
    OIL_OVERHEATING = 3,
};

enum battery_issues_t {
    NOTHING_BATTERY = 0,
    UNLOADED = 1,
    OUTAGE = 2,
};

enum bgf_message_t {
    POSITION_LIGHT = 0,
    LOW_BEAM = 1,
    HIGH_BEAM = 2,
    RIGHT_INDICATOR = 3,
    LEFT_INDICATOR = 4,
};

enum light_status_t {
    OFF = 0,
    ON = 1,
};

enum light_state_t {
    LIGHT_OFF = 0,
    LIGHT_ON = 1,
    LIGHT_ERROR = 2,
    LIGHT_ACQUITTED = 3,
};

enum indicator_state_t {
    INDICATOR_OFF = 0,
    ACTIVATED_OFF = 1,
    ACTIVATED_ON = 2,
    INDICATOR_ERROR = 3,
    INDICATOR_ACQUITTED = 4,
};

enum windscreen_wipers_state_t {
    ALL_OFF = 0,
    WIPERS_ACTIVATED = 1,
    WDSCRN_CLN_WPRS_ACTIVATED = 2,
    TMR_WPRS_WDSCRN_CLN_OFF = 3,
};

typedef struct {
    kilometer_t kilometer;
    rpm_t rpm;
    fuel_t fuel_level;
    mux_frame_number_t frame_number;
    speed_t speed;
    uint8_t chassis_issue;
    uint8_t engine_issue;
    uint8_t battery_issue;
    uint8_t crc8;
} mux_frame_t;

typedef struct {
    kilometer_t kilometer;
    rpm_dashboard_t rpm;
    speed_t speed;
    fuel_t fuel_percent_level;
    dashboard_light_t dashboard_light;
} bcgv_frame_t;

#endif
