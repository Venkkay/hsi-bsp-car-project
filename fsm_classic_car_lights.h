#ifndef FSM_CLASSIC_CAR_LIGHTS_H
#define FSM_CLASSIC_CAR_LIGHTS_H

#include "libs/data_lib/data_management.h"

uint8_t get_next_event(light_state_t current_state, uint8_t cmd_value);
light_state_t fsm_classic_car_lights(light_state_t current_state, uint8_t cmd_value);
void position_light_comodo(light_state_t current_position_light_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer);
void low_beam_comodo(light_state_t current_low_beam_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer);
void high_beam_comodo(light_state_t current_high_beam_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer);

#endif
