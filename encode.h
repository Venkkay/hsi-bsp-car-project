/**
 * \file encode.h
 * \brief Declaration of encoding functions for the main application
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
*/

#ifndef ENCODE_H
#define ENCODE_H

#include "drv_api.h"
#include "libs/data_lib/data_management.h"

/**
 * \brief Encode the data to create the BGF frame
 * \param fr Frame to the information into
 * \param id_message ID of the message for the BGF
 * \param message Message for the BGF
 */
void bgf_encode_frame(bgf_frame_t* fr, uint8_t id_message, uint8_t message);

/**
 * \brief Translate the information from the MUX into the BCGV frame
 * \param[out] bcgv_frame The frame filled with the information the mux
 * \param dashboard_light The lights of car
 * \param speed The speed of the car
 * \param kilometer The kilometer of the car
 * \param fuel The fuel level
 * \param rpm The RPM of the engine
 */
void bcgv_to_mux(bcgv_frame_t* bcgv_frame ,dashboard_light_t dashboard_light, speed_t speed, kilometer_t kilometer, fuel_t fuel, rpm_t rpm);

/**
 * \brief Create the UDP to be sent from the data inside the BCGV frame
 * \param bcgv_frame The frame for retrieving information
 * \param[out] udpFrame The frame created to be sent to the driver
 */
void create_bcgv_to_mux_frame(bcgv_frame_t* bcgv_frame, uint8_t udpFrame[DRV_UDP_200MS_FRAME_SIZE]);

/**
 * \brief   Encode the data decoded into the serial data frame
 * \param[out]   serial_frame : Table with the data to be sent to the serial channel
 * \param        frame : Table with the data to be process for the serial table
 * \param data_length : Length of the table frame
*/
uint8_t encode_serial_frame_bgf(serial_frame_t* serial_frame, bgf_frame_t* frame, bgf_frame_t* previous_frame, uint32_t data_length);
#endif //ENCODE_H
