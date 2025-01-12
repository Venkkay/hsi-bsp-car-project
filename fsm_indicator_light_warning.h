#ifndef FSM_INDICATOR_LIGHT_WARNING_H
#define FSM_INDICATOR_LIGHT_WARNING_H

#include "libs/data_lib/data_management.h"

uint8_t get_next_event(indicator_state_t current_state, uint8_t cmd_value);
indicator_state_t fsm_indicator_light_warning(indicator_state_t current_state, uint8_t cmd_value);
void right_indicator_comodo(indicator_state_t current_right_indicator_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer);
void left_indicator_comodo(indicator_state_t current_left_indicator_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer);
void warning_comodo(indicator_state_t current_warning_state, uint8_t cmd_value, uint8_t /*or size_t*/ timer);

#endif