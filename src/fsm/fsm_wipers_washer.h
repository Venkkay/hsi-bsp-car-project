/**
 * \file fsm_wipers_washer.h
 * \brief Declaration of FSM functions for windscreen wipers and washer
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
 */

#ifndef FSM_WIPERS_WASHER_H
#define FSM_WIPERS_WASHER_H

#include <time.h>

#include "../../libs/data_lib/data_management.h"

/**
 * \brief   Determines the event that will occur using FSM parameters
 * \param   current_state : Current status of a FSM element
 * \param   cmd_wipers_value : Value sent by the comodo for a FSM element
 * \param   cmd_washer_value : Value sent by the comodo for washer
 * \param   timer : Time from which the FSM is requested
 * \return  uint8_t : The value of the next event
 */
uint8_t get_next_event_wipers_washer(wipers_washer_state_t current_state, uint8_t cmd_wipers_value, uint8_t cmd_washer_value, clock_t timer);

/**
 * \brief   Performs the FSM with parameters sent by the system
 * \param   current_state : Current status of windscreen wipers and washer
 * \param   cmd_wipers_value : Value sent by the comodo for windscreen wipers
 * \param   cmd_washer_value : Value sent by the comodo for washer
 * \param   timer : Time from which the FSM is requested
 * \return  wipers_washer_state_t : Returns the state of a FSM element
 */
wipers_washer_state_t fsm_wipers_washer(wipers_washer_state_t current_state, uint8_t cmd_wipers_value, uint8_t cmd_washer_value, clock_t timer);

/**
 * \brief   Initializes the launch of FSM for windscreen wipers and washer
 * \param   current_wipers_washer_state : Current status of windscreen wipers and washer
 * \param   cmd_wipers_value : Value sent by the comodo for windscreen wipers
 * \param   cmd_washer_value : Value sent by the comodo for washer
 * \param   timer : Time from which the FSM is requested
 * \return	wipers_washer_state_t : Returns the state of a FSM element after being timer checked
 */
wipers_washer_state_t wipers_washer_comodo(wipers_washer_state_t current_wipers_washer_state, uint8_t cmd_wipers_value, uint8_t cmd_washer_value, clock_t timer);

#endif