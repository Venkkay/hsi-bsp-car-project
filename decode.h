/**
 * \file decode.h
 * \brief Declaration of decoding functions for the main application
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
*/


#ifndef DECODE_C_H
#define DECODE_C_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "drv_api.h"
#include "libs/data_lib/data_management.h"


/**
 * \brief Translate the information from the UDP frame into the MUX frame
 * \param[out] mux_frame Frame to filled with the information decoded
 * \param udpFrame Frame with the raw information
 */
void decode_mux_frame(mux_frame_t* mux_frame, uint8_t udpFrame[DRV_UDP_100MS_FRAME_SIZE]);

/**
 * \brief Translate the information from Serial frame into the comodo frame
 * \param serial_frame Frame with the raw information
 * \param data_len Length of the data in the input
 * \param[out] comodo_frame Frame filled with the information decoded
 */
void decode_comodo_frame(serial_frame_t serial_frame[DRV_MAX_FRAMES], uint32_t data_len, comodo_frame_t comodo_frame[DRV_MAX_FRAMES]);

/**
 * \brief Translate the information from Serial frame into the BGF frame
 * \param serial_frame Frame with the raw information
 * \param data_len Length of the data in the input
 * \param bgf_frame Frame filled with the information decoded
 */
void decode_bgf_frame(serial_frame_t serial_frame[DRV_MAX_FRAMES], uint32_t data_len, bgf_frame_t bgf_frame[DRV_MAX_FRAMES]);

/**
 * \brief Check the CRC8 of the UDP frame
 * \param data Frame to check
 * \param length Length of the frame
 * \param polynomial CRC8 polynomial
 * \param initial_value Initial CRC value
 * \return CRC8 obtained after the operations
 */
uint8_t check_crc8(uint8_t *data, size_t length, uint8_t polynomial, uint8_t initial_value);

/**
 * \brief Get the information from the MUX to light the dashboard
 * \param mux_frame Frame with the information for the dashboard lights
 * \return Dashboard lights ready to used
 */
dashboard_light_t decode_lights(mux_frame_t* mux_frame);

#endif //DECODE_C_H
