/**
 * \file fsm_classic_car_lights.h
 * \brief Declaration of FSM functions for classic car lights
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
 */

#ifndef FSM_CLASSIC_CAR_LIGHTS_H
#define FSM_CLASSIC_CAR_LIGHTS_H

#include <time.h>

#include "libs/data_lib/data_management.h"

/**
 * \brief   Determines the event that will occur using FSM parameters
 * \param   current_state : Current status of a FSM element
 * \param   cmd_value : Value sent by the comodo for a FSM element
 * \param   timer : Time from which the FSM is requested
 * \return  uint8_t : The value of the next event
 */
uint8_t get_next_event_classic_car_lights(light_state_t current_state, uint8_t cmd_value);

/**
 * \brief   Performs the FSM with parameters sent by the system
 * \param   current_state : Current status of a FSM element
 * \param   cmd_value : Value sent by the comodo for a FSM element
 * \param   timer : Time from which the FSM is requested
 * \return  indicator_state_t : Returns the state of a FSM element
 */
light_state_t fsm_classic_car_lights(light_state_t current_state, uint8_t cmd_value);

/**
 * \brief   Initializes the launch of FSM for position lights
 * \param   current_high_beam_state : Current status of position lights
 * \param   cmd_value : Value sent by the comodo for position lights
 * \param   timer : Time from which the FSM is requested
 * \return  indicator_state_t : Returns the state of a FSM element after being timer checked
 */
light_state_t position_light_comodo(light_state_t current_position_light_state, uint8_t cmd_value, clock_t timer);

/**
 * \brief   Initializes the launch of FSM for low beams lights
 * \param   current_high_beam_state : Current status of low beams lights
 * \param   cmd_value : Value sent by the comodo for low beams lights
 * \param   timer : Time from which the FSM is requested
 * \return  indicator_state_t : Returns the state of a FSM element after being timer checked
 */
light_state_t low_beam_comodo(light_state_t current_low_beam_state, uint8_t cmd_value, clock_t timer);

/**
 * \brief   Initializes the launch of FSM for high beams lights
 * \param   current_high_beam_state : Current status of high beams lights
 * \param   cmd_value : Value sent by the comodo for high beams lights
 * \param   timer : Time from which the FSM is requested
 * \return  indicator_state_t : Returns the state of a FSM element after being timer checked
 */
light_state_t high_beam_comodo(light_state_t current_high_beam_state, uint8_t cmd_value, clock_t timer);

#endif
