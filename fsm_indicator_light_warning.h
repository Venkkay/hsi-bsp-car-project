/**
 * \file fsm_indicator_light_warning.h
 * \brief Declaration of FSM functions for indicator lights and warnings
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
 */

#ifndef FSM_INDICATOR_LIGHT_WARNING_H
#define FSM_INDICATOR_LIGHT_WARNING_H

#include <time.h>

#include "libs/data_lib/data_management.h"

/**
 * \brief   Determines the event that will occur using FSM parameters
 * \param   current_state : Current status of a FSM element
 * \param   cmd_value : Value sent by the comodo for a FSM element
 * \param   timer : Time from which the FSM is requested
 * \return  uint8_t : The value of the next event
 */
uint8_t get_next_event_indicator_light_warning(indicator_state_t current_state, uint8_t cmd_value, clock_t timer);

/**
 * \brief   Performs the FSM with parameters sent by the system
 * \param   current_state : Current status of a FSM element
 * \param   cmd_value : Value sent by the comodo for a FSM element
 * \param   timer : Time from which the FSM is requested
 * \return  indicator_state_t : Returns the state of a FSM element
 */
indicator_state_t fsm_indicator_light_warning(indicator_state_t current_state, uint8_t cmd_value, clock_t timer);

/**
 * \brief   Initializes the launch of FSM for the right indicator light
 * \param   current_right_indicator_state : Current status of the right indicator light
 * \param   cmd_value : Value sent by the comodo for the right indicator light
 * \param   timer : Time from which the FSM is requested
 */
void right_indicator_comodo(indicator_state_t current_right_indicator_state, uint8_t cmd_value, clock_t timer);

/**
 * \brief   Initializes the launch of FSM for the left indicator light
 * \param   current_left_indicator_state : Current status of the left indicator light
 * \param   cmd_value : Value sent by the comodo for the left indicator light
 * \param   timer : Time from which the FSM is requested
 */
void left_indicator_comodo(indicator_state_t current_left_indicator_state, uint8_t cmd_value, clock_t timer);

/**
 * \brief   Initializes the launch of FSM for warnings
 * \param   current_warning_state : Current status of warnings
 * \param   cmd_value : Value sent by the comodo for warnings
 * \param   timer : Time from which the FSM is requested
 */
void warning_comodo(indicator_state_t current_warning_state, uint8_t cmd_value, clock_t timer);

#endif