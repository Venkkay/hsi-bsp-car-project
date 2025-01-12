/**
 * \file fsm_indicator_light_warning.c
 * \brief Declaration of FSM functions for indicator lights and warnings
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "fsm_indicator_light_warning.h"

#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))

typedef struct {
    indicator_state_t state;
    indicator_event_t event;
    uint8_t next_state;
} tTransition;

tTransition trans[] = {
    { ST_INDICATOR_OFF, EV_INDICATOR_CMD_0, ST_INDICATOR_OFF},
    { ST_INDICATOR_OFF, EV_INDICATOR_CMD_1, ST_INDICATOR_ACTIVATED_ON},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_CMD_0, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_CMD_1, ST_INDICATOR_ACTIVATED_ON},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_ACK_NRCV, ST_INDICATOR_ERROR},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_ACK_RCV, ST_INDICATOR_ACQUITTED_ON},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_CMD_0, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_CMD_1, ST_INDICATOR_ACQUITTED_ON},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_TMR_EQ_1, ST_INDICATOR_ACTIVATED_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_CMD_0, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_CMD_1, ST_INDICATOR_ACTIVATED_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_ACK_NRCV, ST_INDICATOR_ERROR},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_ACK_RCV, ST_INDICATOR_ACQUITTED_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_CMD_0, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_CMD_1, ST_INDICATOR_ACQUITTED_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_TMR_EQ_1, ST_INDICATOR_ACTIVATED_ON},
};

uint8_t get_next_event_indicator_light_warning(indicator_state_t current_state, uint8_t cmd_value, clock_t timer) {
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
            } else if (/* timer > 1 sec */) {
                event = EV_INDICATOR_ACK_NRCV;
            } else if (/* timer < 1 sec */) {
                event = EV_INDICATOR_ACK_RCV;
            }
        break;

        case ST_INDICATOR_ACQUITTED_ON:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            } else if ( /* timer == 1 */) {
                event = EV_INDICATOR_TMR_EQ_1;
            }
        break;

        case ST_INDICATOR_ACTIVATED_OFF:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            } else if (/* timer > 1 sec */) {
                event = EV_INDICATOR_ACK_NRCV;
            } else if (/* timer < 1 sec */) {
                event = EV_INDICATOR_ACK_RCV;
            }
        break;

        case ST_INDICATOR_ACQUITTED_OFF:
            if (cmd_value == 0) {
                event = EV_INDICATOR_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_INDICATOR_CMD_1;
            } else if ( /* timer == 1 */) {
                event = EV_INDICATOR_TMR_EQ_1;
            }
        break;

        default:
            /* To complete */
        break;
    }

    return event;
}

indicator_state_t fsm_indicator_light_warning(indicator_state_t current_state, uint8_t cmd_value, clock_t timer) {

    while (current_state != ST_INDICATOR_ERROR) {
        uint8_t event = get_next_event_indicator_light_warning(current_state, cmd_value, timer);

        for (size_t i = 0; i < TRANS_COUNT; i++) {
            if (current_state == trans[i].state) {
                if (event == trans[i].event) {
                    current_state = trans[i].next_state;
                    break;
                }
            }
        }
    }

    return current_state;
}

void right_indicator_comodo(indicator_state_t current_right_indicator_state, uint8_t cmd_value, clock_t timer) {
    if (current_right_indicator_state != ST_INDICATOR_ERROR) {
        indicator_state_t new_state = fsm_indicator_light_warning(current_right_indicator_state, cmd_value, timer);

        if (new_state != current_right_indicator_state) {
            if (/* not ack */) {
                current_right_indicator_state = ST_INDICATOR_ERROR;
            } else if (/* ack */) {
                indicator_state_t new_state_ack = fsm_indicator_light_warning(new_state, cmd_value, timer);
                current_right_indicator_state = new_state_ack;
            }
        }
    }
}

void left_indicator_comodo(indicator_state_t current_left_indicator_state, uint8_t cmd_value, clock_t timer) {
    if (current_left_indicator_state != ST_INDICATOR_ERROR) {
        indicator_state_t new_state = fsm_indicator_light_warning(current_left_indicator_state, cmd_value, timer);

        if (new_state != current_left_indicator_state) {
            if (/* not ack */) {
                current_left_indicator_state = ST_INDICATOR_ERROR;
            } else if (/* ack */) {
                indicator_state_t new_state_ack = fsm_indicator_light_warning(new_state, cmd_value, timer);
                current_left_indicator_state = new_state_ack;
            }
        }
    }
}

void warning_comodo(indicator_state_t current_warning_state, uint8_t cmd_value, clock_t timer) {
    if (current_warning_state != ST_INDICATOR_ERROR) {
        indicator_state_t new_state = fsm_indicator_light_warning(current_warning_state, cmd_value, timer));

        if (new_state != current_warning_state) {
          // communication with BGF
            if (/* not ack */) {
                current_warning_state = ST_INDICATOR_ERROR;
            } else if (/* ack */) {
                indicator_state_t new_state_ack = fsm_indicator_light_warning(new_state, cmd_value, timer);
                current_warning_state = new_state_ack;
            }
        }
    }
}
