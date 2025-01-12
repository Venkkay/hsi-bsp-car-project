#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "fsm_flashing_light_warning.h"

#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))

//static int callback_init (void) { return 0; };
//static int callback_switch_off (void) { return 0; };
//static int callback_active_switch_on (void) { return 0; };
//static int callback_ack_on (void) { return 0; };
//static int callback_active_switch_off (void) { return 0; };
//static int callback_ack_off (void) { return 0; };
//static int callback_any_term (void) { return 0; };
//static int callback_any_error(void) { return 0; };

typedef struct {
    indicator_state_t state;
    indicator_event_t event;
    //int (*callback)(void);
    uint8_t next_state;
} tTransition;

tTransition trans[] = {
    { ST_INDICATOR_OFF, EV_INDICATOR_CMD_0, /* &callback_switch_off, */ ST_INDICATOR_OFF},
    { ST_INDICATOR_OFF, EV_INDICATOR_CMD_1, /* callback_switch_off, */ ST_INDICATOR_ACTIVATED_ON},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_CMD_0, /* callback_active_switch_on, */ ST_INDICATOR_OFF},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_CMD_1, /* callback_active_switch_on, */ ST_INDICATOR_ACTIVATED_ON},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_ACK_NRCV, /* callback_active_switch_on, */ ST_INDICATOR_ERROR},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_ACK_RCV, /* callback_active_switch_on, */ ST_INDICATOR_ACQUITTED_ON},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_CMD_0, /* callback_ack_on, */ ST_INDICATOR_OFF},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_CMD_1, /* callback_ack_on, */ ST_INDICATOR_ACQUITTED_ON},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_ACK_NRCV, /* callback_ack_on, */ ST_INDICATOR_ACTIVATED_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_CMD_0, /* callback_active_switch_off, */ ST_INDICATOR_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_CMD_1, /* callback_active_switch_off, */ ST_INDICATOR_ACTIVATED_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_ACK_NRCV, /* callback_active_switch_off, */ ST_INDICATOR_ERROR},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_ACK_RCV, /* callback_active_switch_off, */ ST_INDICATOR_ACQUITTED_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_CMD_0, /* callback_ack_off, */ ST_INDICATOR_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_CMD_1, /* callback_ack_off, */ ST_INDICATOR_ACQUITTED_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_TMR_EQ_1, /* callback_ack_off, */ ST_INDICATOR_ACTIVATED_ON},
};

uint8_t get_next_event(indicator_state_t current_state, uint8_t cmd_value) {
    uint8_t event;

    switch (current_state) {
        case ST_INDICATOR_OFF:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            }
        break;

        case ST_INDICATOR_ACTIVATED_ON:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            }
        break;

        case ST_INDICATOR_ACQUITTED_ON:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            }
        break;

        case ST_INDICATOR_ACTIVATED_OFF:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            }
        break;

        case ST_INDICATOR_ACQUITTED_OFF:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            }
        break;

        default:
            /* To complete */
        break;
    }

    return event;
}

indicator_state_t fsm_indicator_light_warning(indicator_state_t current_state, uint8_t cmd_value) {

    while (current_state != ST_INDICATOR_ERROR) {
        uint8_t event = get_next_event(current_state, cmd_value);

        for (size_t i = 0; i < TRANS_COUNT; i++) {
            if (current_state == trans[i].state) {
                if (event == trans[i].event) {
                    current_state = trans[i].next_state;
                    /*if (trans[i].callback != callback_null) {
                        Call the state function
                        ret = (trans[i].callback)();
                    }*/
                    break;
                }
            }
        }
    }

    return current_state;
}

void right_indicator_comodo(indicator_state_t current_right_indicator_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer) {
    if (current_right_indicator_state != ST_INDICATOR_ERROR) {
        indicator_state_t new_state = fsm_indicator_light_warning(current_right_indicator_state, cmd_value);

        if (new_state != current_right_indicator_state) {
            // communication with BGF
            // wait 1 sec max

            if (/* not ack */) {
                current_right_indicator_state = ST_INDICATOR_ERROR;
            } else if (/* ack */) {
                indicator_state_t new_state_ack = fsm_indicator_light_warning(new_state, cmd_value);
                // communication with BGF
                current_right_indicator_state = new_state_ack;
            }
        }
    }
}

void left_indicator_comodo(indicator_state_t current_left_indicator_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer) {
    if (current_left_indicator_state != ST_INDICATOR_ERROR) {
        indicator_state_t new_state = fsm_indicator_light_warning(current_left_indicator_state, cmd_value);

        if (new_state != current_left_indicator_state) {
            // communication with BGF
            // wait 1 sec max

            if (/* not ack */) {
                current_left_indicator_state = ST_INDICATOR_ERROR;
            } else if (/* ack */) {
                indicator_state_t new_state_ack = fsm_indicator_light_warning(new_state, cmd_value);
                // communication with BGF
                current_left_indicator_state = new_state_ack;
            }
        }
    }
}

void warning_comodo(indicator_state_t current_warning_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer) {
    if (current_warning_state != ST_INDICATOR_ERROR) {
        indicator_state_t new_state = fsm_indicator_light_warning(current_warning_state, cmd_value);

        if (new_state != current_warning_state) {
            // communication with BGF
            // wait 1 sec max

            if (/* not ack */) {
                current_warning_state = ST_INDICATOR_ERROR;
            } else if (/* ack */) {
                indicator_state_t new_state_ack = fsm_indicator_light_warning(new_state, cmd_value);
                // communication with BGF
                current_warning_state = new_state_ack;
            }
        }
    }
}
