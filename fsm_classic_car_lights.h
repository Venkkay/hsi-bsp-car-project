#ifndef FSM_CLASSIC_CAR_LIGHTS_H
#define FSM_CLASSIC_CAR_LIGHTS_H

#include "libs/data_lib/data_management.h"

light_state_t fsm_classic_car_lights(light_state_t current_state, uint8_t value);

#endif //FSM_CLASSIC_CAR_LIGHTS_H
