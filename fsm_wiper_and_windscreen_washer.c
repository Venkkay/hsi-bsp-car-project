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

/* States */
typedef enum {
    ST_ANY = -1,                            /* Any state */
    ST_INIT = 0,                            /* Init state */
    ST_ALL_SWITCH_OFF = 9,
    ST_WSW_ON = 10,
    ST_SW_WSW_ON = 11,
    ST_TMR_WSW_SW_OFF = 12,
    ST_TERM = 255                           /* Final state */
} fsm_state_t;

/* Events */
typedef enum {
    EV_ANY = -1,                            /* Any event */
    EV_NONE = 0,                            /* No event */
    EV_CMD_EG_0_CMD_LG_0 = 5,
    EV_CMD_EG_0 = 6,
    EV_CMD_EG_1 = 7,
    EV_CMD_LG_0 = 8,
    EV_CMD_LG_1 = 9,
    EV_TMR_GT2 = 10,
    EV_TMR_LT2 = 10,
    EV_ERR = 255                            /* Error event */
} fsm_event_t;

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
    fsm_state_t state;
    fsm_event_t event;
    int (*callback)(void);
    int next_state;
} tTransition;

/* Transition table */
tTransition trans[] = {
    /* These are examples */
    { ST_INIT, EV_NONE, &callback_init, ST_ALL_SWITCH_OFF},
    { ST_ALL_SWITCH_OFF, EV_CMD_EG_0_CMD_LG_0, &callback_all_switch_off, ST_ALL_SWITCH_OFF},
    { ST_ALL_SWITCH_OFF, EV_CMD_EG_1, &callback_all_switch_off, ST_WSW_ON},
    { ST_ALL_SWITCH_OFF, EV_CMD_LG_1, &callback_all_switch_off, ST_SW_WSW_ON},
    { ST_WSW_ON, EV_CMD_EG_0, &callback_wsw_on_all_switch_off, ST_ALL_SWITCH_OFF},
    { ST_WSW_ON, EV_CMD_EG_1, &callback_wsw_on_loop, ST_WSW_ON},
    { ST_WSW_ON, EV_CMD_LG_1, &callback_wsw_sw_wsw_on, ST_SW_WSW_ON},
    { ST_SW_WSW_ON, EV_CMD_LG_1, &callback_sw_wsw_on_loop, ST_SW_WSW_ON},
    { ST_SW_WSW_ON, EV_CMD_LG_0, &callback_sw_wsw_on_wsw_sw_off, ST_TMR_WSW_SW_OFF},
    { ST_TMR_WSW_SW_OFF, EV_TMR_LT2, &callback_tmr_wsw_sw_off_loop, ST_TMR_WSW_SW_OFF},
    { ST_TMR_WSW_SW_OFF, EV_TMR_GT2, &callback_tmr_wsw_sw_off_all_switch_off, ST_ALL_SWITCH_OFF},
    { ST_ANY, EV_ANY, &callback_any_term, ST_TERM},
    { ST_ANY, EV_ERR, &callback_any_error, ST_TERM}
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
    int event = EV_NONE;
    int state = ST_INIT;

    /* While FSM hasn't reach end state */
    while (state != ST_TERM) {

        /* Get event */
        event = get_next_event(state);

        /* For each transitions */
        for (i = 0; i < TRANS_COUNT; i++) {
            /* If State is current state OR The transition applies to all states ...*/
            if ((state == trans[i].state) || (ST_ANY == trans[i].state)) {
                /* If event is the transition event OR the event applies to all */
                if ((event == trans[i].event) || (EV_ANY == trans[i].event)) {
                    /* Apply the new state */
                    state = trans[i].next_state;
                    if (trans[i].callback != NULL) {
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
