/**
 * \file        fsm_classic_car_lights.c
 * \author      Yann Etrillard
 * \version     0.1
 * \date        19 december 2024
 * \brief       This is a file for the Finite State Machine for classic car lights.
 * \details
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fsm_classic_car_lights.h"
#include "libs/data_lib/data_management.h"

/* Callback functions called on transitions */
static int callback_init (void) { return 0; };
static int callback_switch_off_loop (void) { return 0; };
static int callback_switch_off_switch_on (void) { return 0; };
static int callback_switch_on_switch_off (void) { return 0; };
static int callback_switch_on_loop (void) { return 0; };
static int callback_switch_on_ack (void) { return 0; };
static int callback_switch_on_error (void) { return 0; };
static int callback_ack_switch_off (void) { return 0; };
static int callback_ack_loop (void) { return 0; };
static int callback_any_term (void) { return 0; };
static int callback_any_error(void) { return 0; };

/* Transition structure */
typedef struct {
    light_state_t state;
    light_event_t event;
    int (*callback)(void);
    int next_state;
} tTransition;

/* Transition table */
tTransition trans[] = {
    { ST_LIGHT_INIT, EV_LIGHT_NONE, &callback_init, ST_LIGHT_OFF},
    { ST_LIGHT_OFF, EV_LIGHT_CMD_0, &callback_switch_off_loop, ST_LIGHT_OFF},
    { ST_LIGHT_OFF, EV_LIGHT_CMD_1, &callback_switch_off_switch_on, ST_LIGHT_ON},
    { ST_LIGHT_ON, EV_LIGHT_CMD_0, &callback_switch_on_switch_off, ST_LIGHT_OFF},
    { ST_LIGHT_ON, EV_LIGHT_CMD_1, &callback_switch_on_loop, ST_LIGHT_ON},
    { ST_LIGHT_ON, EV_LIGHT_ACK_RCV, &callback_switch_on_ack, ST_LIGHT_ACQUITTED},
    { ST_LIGHT_ON, EV_LIGHT_ACK_NRCV, &callback_switch_on_error, ST_LIGHT_ERROR},
    { ST_LIGHT_ACQUITTED, EV_LIGHT_CMD_0, &callback_ack_switch_off, ST_LIGHT_OFF},
    { ST_LIGHT_ACQUITTED, EV_LIGHT_CMD_1, &callback_ack_loop, ST_LIGHT_ACQUITTED},
    { ST_LIGHT_ANY, EV_LIGHT_ANY, &callback_any_term, ST_LIGHT_TERM}, /* not considered at this time */
    { ST_LIGHT_ANY, EV_LIGHT_ERROR, &callback_any_error, ST_LIGHT_TERM}
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
    int event = EV_LIGHT_NONE;
    int state = ST_LIGHT_INIT;

    /* While FSM hasn't reach end state */
    while (state != ST_TERM) {

        /* Get event */
        event = get_next_event(state);

        /* For each transitions */
        for (i = 0; i < TRANS_COUNT; i++) {
            /* If State is current state OR The transition applies to all states ...*/
            if ((state == trans[i].state) || (ST_LIGHT_ANY == trans[i].state)) {
                /* If event is the transition event OR the event applies to all */
                if ((event == trans[i].event) || (EV_LIGHT_ANY == trans[i].event)) {
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
