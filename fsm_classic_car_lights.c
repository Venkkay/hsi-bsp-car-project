#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "fsm_classic_car_lights.h"

#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))

//static int callback_switch_off_loop (void) { return 0; };/* à supprimer si pas de callack */
//static int callback_switch_off_switch_on (void) { return 0; };
//static int callback_switch_on_switch_off (void) { return 0; };
//static int callback_switch_on_loop (void) { return 0; };/* à supprimer si pas de callack */
//static int callback_switch_on_ack (void) { return 0; };
//static int callback_switch_on_error (void) { return 0; };
//static int callback_ack_switch_off (void) { return 0; };
//static int callback_ack_loop (void) { return 0; };/* à supprimer si pas de callack */

typedef struct {
    light_state_t state;
    light_event_t event;
    //int (*callback)(void);
    uint8_t next_state;
} tTransition;

tTransition trans[] = {
    { ST_LIGHT_OFF, EV_LIGHT_CMD_0, /* &callback_switch_off_loop, */ ST_LIGHT_OFF},
    { ST_LIGHT_OFF, EV_LIGHT_CMD_1, /* &callback_switch_off_switch_on, */ ST_LIGHT_ON},
    { ST_LIGHT_ON, EV_LIGHT_CMD_0, /* &callback_switch_on_switch_off, */ ST_LIGHT_OFF},
    { ST_LIGHT_ON, EV_LIGHT_CMD_1, /* &callback_switch_on_loop, */ ST_LIGHT_ON},
    { ST_LIGHT_ON, EV_LIGHT_ACK_RCV, /* &callback_switch_on_ack, */ ST_LIGHT_ACQUITTED},
    { ST_LIGHT_ON, EV_LIGHT_ACK_NRCV, /* &callback_switch_on_error, */ ST_LIGHT_ERROR},
    { ST_LIGHT_ACQUITTED, EV_LIGHT_CMD_0, /* &callback_ack_switch_off, */ ST_LIGHT_OFF},
    { ST_LIGHT_ACQUITTED, EV_LIGHT_CMD_1, /* &callback_ack_loop, */ ST_LIGHT_ACQUITTED},
};

uint8_t get_next_event(light_state_t current_state, uint8_t cmd_value) {
    uint8_t event;

    switch (current_state) {
        case ST_LIGHT_OFF:
            if (cmd_value == 0) {
                event = EV_LIGHT_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_LIGHT_CMD_1;
            }
        break;

        case ST_LIGHT_ON:
            if (cmd_value == 0) {
                event = EV_LIGHT_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_LIGHT_CMD_1;
            }
        break;

        case ST_LIGHT_ACQUITTED:
            if (cmd_value == 0) {
                event = EV_LIGHT_CMD_0;
            } else if (cmd_value == 1) {
                event = EV_LIGHT_CMD_1;
            }
        break;

        default:
			/* To complete */
        break;
    }

    return event;
}

light_state_t fsm_classic_car_lights(light_state_t current_state, uint8_t cmd_value) {

    while (current_state != ST_LIGHT_ERROR) {
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

void position_light_comodo(light_state_t current_position_light_state, uint8_t cmd_value, uint8_t /*or size_t*/ compteur) {
  if (current_position_light_state != ST_LIGHT_ERROR) {
    light_state_t new_state = fsm_classic_car_lights(current_position_light_state, cmd_value);

    if (new_state != current_position_light_state) {
      // communication with BGF
      // wait 1 sec max

      if (/* not ack */) {
      	current_position_light_state = ST_LIGHT_ERROR;
      } else if (/* ack */) {
      	light_state_t new_state_ack = fsm_classic_car_lights(new_state, cmd_value);
      	// communication with BGF
      	current_position_light_state = new_state_ack;
      }
    }
  }
}

void low_beam_comodo(light_state_t current_low_beam_state, uint8_t cmd_value, uint8_t /*or size_t*/ compteur) {
  if (current_low_beam_state != ST_LIGHT_ERROR) {
    light_state_t new_state = fsm_classic_car_lights(current_low_beam_state, cmd_value);

    if (new_state != current_low_beam_state) {
      // communication with BGF
      // wait 1 sec max

      if (/* not ack */) {
      	current_low_beam_state = ST_LIGHT_ERROR;
      } else if (/* ack */) {
      	light_state_t new_state_ack = fsm_classic_car_lights(new_state, cmd_value);
      	// communication with BGF
      	current_low_beam_state = new_state_ack;
      }
    }
  }
}

void high_beam_comodo(light_state_t current_high_beam_state, uint8_t cmd_value, uint8_t /*or size_t*/ compteur) {
  if (current_high_beam_state != ST_LIGHT_ERROR) {
    light_state_t new_state = fsm_classic_car_lights(current_high_beam_state, cmd_value);

    if (new_state != current_high_beam_state) {
      // communication with BGF
      // wait 1 sec max

      if (/* not ack */) {
      	current_high_beam_state = ST_LIGHT_ERROR;
      } else if (/* ack */) {
      	light_state_t new_state_ack = fsm_classic_car_lights(new_state, cmd_value);
      	// communication with BGF
      	current_high_beam_state = new_state_ack;
      }
    }
  }
}
