/**
 * \file        fsm_flashing_lights_warnings.c
 * \author      Yann Etrillard
 * \version     0.1
 * \date        20 december 2024
 * \brief       This is a file for the Finite State Machine for flashing car lights and warnings.
 * \details
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fsm_flashing_lights_warnings.h"
#include "libs/data_lib/data_management.h"

/* Callback functions called on transitions */
static int callback_init (void) { return 0; };
static int callback_switch_off (void) { return 0; };
static int callback_active_switch_on (void) { return 0; };
static int callback_ack_on (void) { return 0; };
static int callback_active_switch_off (void) { return 0; };
static int callback_ack_off (void) { return 0; };
static int callback_any_term (void) { return 0; };
static int callback_any_error(void) { return 0; };

/* Transition structure */
typedef struct {
    indicator_state_t state;
    indicator_event_t event;
    int (*callback)(void);
    int next_state;
} tTransition;

/* Transition table */
tTransition trans[] = {
    /* These are examples */
    { ST_INDICATOR_INIT, EV_INDICATOR_NONE, &callback_init, ST_INDICATOR_OFF},
    { ST_INDICATOR_OFF, EV_INDICATOR_CMD_0, &callback_switch_off, ST_INDICATOR_OFF},
    { ST_INDICATOR_OFF, EV_INDICATOR_CMD_1, &callback_switch_off, ST_INDICATOR_ACTIVATED_ON},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_CMD_0, &callback_active_switch_on, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_CMD_1, &callback_active_switch_on, ST_INDICATOR_ACTIVATED_ON},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_ACK_NRCV, &callback_active_switch_on, ST_INDICATOR_ERROR},
    { ST_INDICATOR_ACTIVATED_ON, EV_INDICATOR_ACK_RCV, &callback_active_switch_on, ST_INDICATOR_ACQUITTED_ON},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_CMD_0, &callback_ack_on, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_CMD_1, &callback_ack_on, ST_INDICATOR_ACQUITTED_ON},
    { ST_INDICATOR_ACQUITTED_ON, EV_INDICATOR_ACK_NRCV, &callback_ack_on, ST_INDICATOR_ACTIVATED_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_CMD_0, &callback_active_switch_off, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_CMD_1, &callback_active_switch_off, ST_INDICATOR_ACTIVATED_OFF},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_ACK_NRCV, &callback_active_switch_off, ST_INDICATOR_ERROR},
    { ST_INDICATOR_ACTIVATED_OFF, EV_INDICATOR_ACK_RCV, &callback_active_switch_off, ST_INDICATOR_ACQUITTED_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_CMD_0, &callback_ack_off, ST_INDICATOR_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_CMD_1, &callback_ack_off, ST_INDICATOR_ACQUITTED_OFF},
    { ST_INDICATOR_ACQUITTED_OFF, EV_INDICATOR_TMR_EQ_1, &callback_ack_off, ST_INDICATOR_ACTIVATED_ON},
    { ST_INDICATOR_ANY, EV_INDICATOR_ANY, &callback_any_term, ST_INDICATOR_TERM}, /* not considered at this time */
    { ST_INDICATOR_ANY, EV_INDICATOR_ERROR, &callback_any_error, ST_INDICATOR_TERM}
};

#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))

int get_next_event(int current_state) {
    int event;
    /* Here, you can get the parameters of your FSM */
    /* Build all the events */
    /* Example code :
    if (PARAM1 == ...) {
        event = EV_EVENT1
    }
    else if (PARAM2 == ... && PARAM3 == ...) {
        event = EV_EVENT2
    }
    ... */

    return event;
}

int main(void) {
    int i = 0;
    int ret = 0;
    int event = EV_INDICATOR_NONE;
    int state = ST_INDICATOR_INIT;

    /* While FSM hasn't reach end state */
    while (state != ST_TERM) {

        /* Get event */
        event = get_next_event(state);

        /* For each transitions */
        for (i = 0; i < TRANS_COUNT; i++) {
            /* If State is current state OR The transition applies to all states ...*/
            if ((state == trans[i].state) || (ST_INDICATOR_ANY == trans[i].state)) {
                /* If event is the transition event OR the event applies to all */
                if ((event == trans[i].event) || (EV_INDICATOR_ANY == trans[i].event)) {
                    /* Apply the new state */
                    state = trans[i].next_state;
                    if (trans[i].callback != callback_null) {
                        /* Call the state function */
                        ret = (trans[i].callback)();
                    }
                    break;
                }
            }
        }
    }

    return ret;
}
