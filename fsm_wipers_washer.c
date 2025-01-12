/**
 * \file fsm_wipers_washer.c
 * \brief Declaration of FSM functions for windscreen wipers and washer
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "fsm_wipers_washer.h"

#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))

typedef struct {
    wipers_washer_state_t state;
    wipers_washer_event_t event;
    uint8_t next_state;
} tTransition;

tTransition trans[] = {
    { ST_WP_WS_ALL_OFF, EV_WP_WS_CMD_WP_0_CMD_WS_0, ST_WP_WS_ALL_OFF},
    { ST_WP_WS_ALL_OFF, EV_WP_WS_CMD_WP_1, ST_WP_ON},
    { ST_WP_WS_ALL_OFF, EV_WP_WS_CMD_WS_1, ST_WP_WS_ON},
    { ST_WP_ON, EV_WP_WS_CMD_WP_0, ST_WP_WS_ALL_OFF},
    { ST_WP_ON, EV_WP_WS_CMD_WP_1, ST_WP_ON},
    { ST_WP_ON, EV_WP_WS_CMD_WS_1, ST_WP_WS_ON},
    { ST_WP_WS_ON, EV_WP_WS_CMD_WS_0, ST_TMR_WP_WS_OFF},
    { ST_WP_WS_ON, EV_WP_WS_CMD_WS_1, ST_WP_WS_ON},
    { ST_TMR_WP_WS_OFF, EV_WP_WS_CMD_WS_1, ST_WP_WS_ON},
    { ST_TMR_WP_WS_OFF, EV_WP_WS_TMR_LT2, ST_TMR_WP_WS_OFF},
    { ST_TMR_WP_WS_OFF, EV_WP_WS_TMR_GT2, ST_WP_WS_ALL_OFF},
};

uint8_t get_next_event_wipers_washer(wipers_washer_state_t current_state, uint8_t cmd_wipers_value, uint8_t cmd_washer_value, clock_t timer) {
    uint8_t event;

    switch (current_state) {
        case ST_WP_WS_ALL_OFF:
            if (cmd_wipers_value == 0 && cmd_washer_value == 0) {
                event = EV_WP_WS_CMD_WP_0_CMD_WS_0;
            } else if (cmd_wipers_value == 1) {
                event = EV_WP_WS_CMD_WP_1;
            } else if (cmd_washer_value == 1) {
                event = EV_WP_WS_CMD_WS_1;
            }
        break;

        case ST_WP_ON:
            if (cmd_wipers_value == 0) {
                event = EV_WP_WS_CMD_WP_0;
            } else if (cmd_wipers_value == 1) {
                event = EV_WP_WS_CMD_WP_1;
            } else if (cmd_washer_value == 1) {
                event = EV_WP_WS_CMD_WP_1;
            }
        break;

        case ST_WP_WS_ON:
            if (cmd_washer_value == 0) {
                event = EV_WP_WS_CMD_WS_0;
            } else if (cmd_washer_value == 1) {
                event = EV_WP_WS_CMD_WS_1;
            }
        break;

        case ST_TMR_WP_WS_OFF:
            if (cmd_washer_value == 1) {
                event = EV_WP_WS_CMD_WS_1;
            } else if (/* timer < 2 sec*/) {
                event = EV_WP_WS_TMR_LT2;
            } else if (/* timer > 2 sec*/) {
                event = EV_WP_WS_TMR_GT2;
            }
        break;

        default:
            /* To complete */
        break;
    }

    return event;
}

wipers_washer_state_t fsm_wipers_washer(wipers_washer_state_t current_state, uint8_t cmd_wipers_value, uint8_t cmd_washer_value, clock_t timer) {
    uint8_t event = get_next_event(current_state, cmd_wipers_value, cmd_washer_value, timer);

    for (size_t i = 0; i < TRANS_COUNT; i++) {
        if (current_state == trans[i].state) {
            if (event == trans[i].event) {
                current_state = trans[i].next_state;
                break;
            }
        }
    }

    return current_state;
}

void wipers_washer_comodo(wipers_washer_state_t current_wipers_washer_state, uint8_t cmd_wipers_value, uint8_t cmd_washer_value, clock_t timer) {
    wipers_washer_state_t new_state = fsm_wipers_washer(current_wipers_washer_state, cmd_wipers_value, cmd_washer_value, timer);

    if (new_state != current_wipers_washer_state) {
        // communication with BGF

        if (new_state == ST_TMR_WP_WS_OFF) {
            // wait 2 sec max
            if (/* timer > 2 */) {
                current_wipers_washer_state = ST_WS_WP_ALL_OFF;
            } else if (/* timer < 2 */) {
                wipers_washer_state_t new_state_tmr = fsm_wipers_washer(new_state, cmd_wipers_value, cmd_washer_value, timer);
                // communication with BGF
                current_wipers_washer_state = new_state_tmr;
            }
        }
    }
}