/**
 * \file fsm_classic_car_lights.h
 * \brief Declaration of FSM functions for classic car lights
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "fsm_classic_car_lights.h"

#define TRANS_COUNT (sizeof(trans_lights)/sizeof(*trans_lights))

typedef struct {
    light_state_t state;
    light_event_t event;
    uint8_t next_state;
} tTransition;

tTransition trans_lights[] = {
    { ST_LIGHT_OFF, EV_LIGHT_CMD_0, ST_LIGHT_OFF },
    { ST_LIGHT_OFF, EV_LIGHT_CMD_1, ST_LIGHT_ON },
    { ST_LIGHT_ON, EV_LIGHT_CMD_0, ST_LIGHT_OFF },
    { ST_LIGHT_ON, EV_LIGHT_CMD_1, ST_LIGHT_ON },
    { ST_LIGHT_ON, EV_LIGHT_ACK_RCV, ST_LIGHT_ACQUITTED },
    { ST_LIGHT_ON, EV_LIGHT_ACK_NRCV, ST_LIGHT_ERROR },
    { ST_LIGHT_ACQUITTED, EV_LIGHT_CMD_0, ST_LIGHT_OFF },
    { ST_LIGHT_ACQUITTED, EV_LIGHT_CMD_1, ST_LIGHT_ACQUITTED },
};

uint8_t get_next_event_classic_car_lights(light_state_t current_state, uint8_t cmd_value) {
    light_event_t event = EV_LIGHT_CMD_0;

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
        light_event_t event = get_next_event_classic_car_lights(current_state, cmd_value);

        for (size_t i = 0; i < TRANS_COUNT; i++) {
            if (current_state == trans_lights[i].state) {
                if (event == trans_lights[i].event) {
                    current_state = trans_lights[i].next_state;
                    break;
                }
            }
        }
    }

    return current_state;
}

light_state_t position_light_comodo(light_state_t current_position_light_state, uint8_t cmd_value, clock_t start_timer) {
	uint64_t elapsed_seconds = 0;
    if (current_position_light_state != ST_LIGHT_ERROR) {
      	if(start_timer != 0){
    		clock_t current_time = clock();
    		elapsed_seconds = (uint64_t)((double)(current_time - start_timer) / CLOCKS_PER_SEC);
    	}

      	light_state_t new_state = fsm_classic_car_lights(current_position_light_state, cmd_value);

    	if (new_state != current_position_light_state) {

        	if (elapsed_seconds >= 1) {
      		  current_position_light_state = ST_LIGHT_ERROR;
        	} else if (elapsed_seconds > 0 && elapsed_seconds < 1) {
      		  return new_state;
      		}else {
        	  return current_position_light_state;
        	}
      	}
        return current_position_light_state;
    }
    return current_position_light_state;
}

light_state_t low_beam_comodo(light_state_t current_low_beam_state, uint8_t cmd_value, clock_t start_timer) {
  uint64_t elapsed_seconds = 0;
    if (current_low_beam_state != ST_LIGHT_ERROR) {
      	if(start_timer != 0){
    		clock_t current_time = clock();
    		elapsed_seconds = (uint64_t)((double)(current_time - start_timer) / CLOCKS_PER_SEC);
    	}

    	light_state_t new_state = fsm_classic_car_lights(current_low_beam_state, cmd_value);

        if (new_state != current_low_beam_state) {

            if (elapsed_seconds >= 1) {
            current_low_beam_state = ST_LIGHT_ERROR;
            } else if (elapsed_seconds > 0 && elapsed_seconds < 1) {
      		  return new_state;
      		}else {
        	  return current_low_beam_state;
        	}
        }
        return current_low_beam_state;
    }
    return current_low_beam_state;
}

light_state_t high_beam_comodo(light_state_t current_high_beam_state, uint8_t cmd_value, clock_t start_timer) {
	uint64_t elapsed_seconds = 0;

	if (current_high_beam_state != ST_LIGHT_ERROR) {
		if(start_timer != 0){
			clock_t current_time = clock();
			elapsed_seconds = (uint64_t)((double)(current_time - start_timer) / CLOCKS_PER_SEC);
		}
		light_state_t new_state = fsm_classic_car_lights(current_high_beam_state, cmd_value);

		if (new_state != current_high_beam_state) {
			if (elapsed_seconds >= 1) {
				current_high_beam_state = ST_LIGHT_ERROR;
			}else if (elapsed_seconds > 0 && elapsed_seconds < 1) {
				return new_state;
			}else{
				return current_high_beam_state;
			}
		}
	}
	return current_high_beam_state;
}
