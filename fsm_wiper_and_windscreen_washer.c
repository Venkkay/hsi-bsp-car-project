/**
 * \file        fsm_wiper_and_windscreen_washer.c
 * \author      Yann Etrillard
 * \version     0.1
 * \date        20 december 2024
 * \brief       This is a file for the Finite State Machine for wiper and windscreen washer.
 * \details
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "fsm_wiper_and_windscreen_washer.h"
#include "libs/data_lib/data_management.h"

/* Callback functions called on transitions */
static int callback_init (void) { return 0; };
static int callback_all_switch_off (void) { return 0; };
static int callback_wsw_on_all_switch_off (void) { return 0; };
static int callback_wsw_on_loop (void) { return 0; };
static int callback_wsw_sw_wsw_on (void) { return 0; };
static int callback_sw_wsw_on_loop (void) { return 0; };
static int callback_sw_wsw_on_wsw_sw_off (void) { return 0; };
static int callback_tmr_wsw_sw_off_loop (void) { return 0; };
static int callback_tmr_wsw_sw_off_all_switch_off (void) { return 0; };
static int callback_any_term (void) { return 0; };
static int callback_any_error(void) { return 0; };

/* Transition structure */
typedef struct {
    windscreen_wipers_state_t state;
    windscreen_wipers_event_t event;
    int (*callback)(void);
    int next_state;
} tTransition;

/* Transition table */
tTransition trans[] = {
    /* These are examples */
    { ST_WS_WP_INIT, EV_WS_WP_NONE, &callback_init, ST_WS_WP_ALL_OFF},
    { ST_WS_WP_ALL_OFF, EV_WS_WP_CMD_EG_0, &callback_all_switch_off, ST_WS_WP_ALL_OFF},
    { ST_WS_WP_ALL_OFF, EV_WS_WP_CMD_EG_1, &callback_all_switch_off, ST_WP_ACTIVATED},
    { ST_WS_WP_ALL_OFF, EV_WS_WP_CMD_LG_1, &callback_all_switch_off, ST_WS_WP_ON},
    { ST_WP_ACTIVATED, EV_WS_WP_CMD_EG_0, &callback_wsw_on_all_switch_off, ST_WS_WP_ALL_OFF},
    { ST_WP_ACTIVATED, EV_WS_WP_CMD_EG_1, &callback_wsw_on_loop, ST_WP_ACTIVATED},
    { ST_WP_ACTIVATED, EV_WS_WP_CMD_LG_1, &callback_wsw_sw_wsw_on, ST_WS_WP_ON},
    { ST_WS_WP_ON, EV_WS_WP_CMD_LG_1, &callback_sw_wsw_on_loop, ST_WS_WP_ON},
    { ST_WS_WP_ON, EV_WS_WP_CMD_LG_0, &callback_sw_wsw_on_wsw_sw_off, ST_TMR_WP_WS_OFF},
    { ST_TMR_WP_WS_OFF, EV_WS_WP_TMR_LT2, &callback_tmr_wsw_sw_off_loop, ST_TMR_WP_WS_OFF},
    { ST_TMR_WP_WS_OFF, EV_WS_WP_TMR_GT2, &callback_tmr_wsw_sw_off_all_switch_off, ST_WS_WP_ALL_OFF},
    { ST_WS_WP_ANY, EV_WS_WP_ANY, &callback_any_term, ST_WS_WP_TERM}, /* not considered at this time */
    { ST_WS_WP_ANY, EV_WS_WP_ERROR, &callback_any_error, ST_WS_WP_TERM}
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
    int event = EV_WS_WP_NONE;
    int state = ST_WS_WP_INIT;

    /* While FSM hasn't reach end state */
    while (state != ST_WS_WP_TERM) {

        /* Get event */
        event = get_next_event(state);

        /* For each transitions */
        for (i = 0; i < TRANS_COUNT; i++) {
            /* If State is current state OR The transition applies to all states ...*/
            if ((state == trans[i].state) || (ST_WS_WP_ANY == trans[i].state)) {
                /* If event is the transition event OR the event applies to all */
                if ((event == trans[i].event) || (EV_WS_WP_ANY == trans[i].event)) {
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
