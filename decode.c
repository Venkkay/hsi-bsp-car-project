/**
 * \file decode.c
 * \brief Decoding functions for the main application
 * \authors Romain Barré, Lucas Velay, Yann Etrillard
*/

#include "decode.h"
/*
TODO

Donnée reçu en sérial sont mélangé. A la fois la commodo et BGF => Prendre que COMMODO

serial_frame_t
uint32_t serNum;                    Physical ser number  == 11 pour commodo
uint8_t frame[SER_MAX_FRAME_SIZE (2)];  Frame received/to write == frame a récupérer pour comodo_frame_t[]
size_t frameSize;                   Size of received frame  == taille de la frame reçu

Reception du MUX => drv
uint8_t udpFrame[DRV_UDP_100MS_FRAME_SIZE (15)] == toutes les infos connus

*/

void decode_mux_frame(mux_frame_t* mux_frame, uint8_t udpFrame[DRV_UDP_100MS_FRAME_SIZE]){


  uint32_t temp_kilometer = udpFrame[1];
  temp_kilometer = (temp_kilometer << 8) | udpFrame[2];
  temp_kilometer = (temp_kilometer << 8) | udpFrame[3];
  temp_kilometer = (temp_kilometer << 8) | udpFrame[4];

  rpm_t temp_rpm = udpFrame[9];
  temp_rpm = (temp_rpm << 8) | udpFrame[10];
  temp_rpm = (temp_rpm << 8) | udpFrame[11];
  temp_rpm = (temp_rpm << 8) | udpFrame[12];

  uint8_t crc8 = udpFrame[14];
  uint8_t polynomial = 0x31; // CRC8 polynomial
  uint8_t initial_value = 0x00; // Initial CRC value

  uint8_t computed_crc = check_crc8(udpFrame, DRV_UDP_100MS_FRAME_SIZE-1, polynomial, initial_value);

  if (computed_crc == crc8) {
    if(set_mux_frame_t(mux_frame, temp_kilometer, temp_rpm, udpFrame[8], udpFrame[0], udpFrame[5], udpFrame[6], udpFrame[7], udpFrame[13], crc8) == false){
		printf("ERROR - set_mux_frame_t failed : %s(%d)\n", strerror(errno), errno);
    }
  } else {
    printf("ERROR - CRC8 failed : %s(%d)\n", strerror(errno), errno);
  }
}

dashboard_light_t decode_lights(mux_frame_t* mux_frame){
  	dashboard_light_t temp_light = 0;

	chassis_issues_t chassis_issues = get_chassis_issue_from_mux_frame_t(*mux_frame);
    engine_issues_t engine_issues = get_engine_issue_from_mux_frame_t(*mux_frame);
    battery_issues_t battery_issues = get_battery_issue_from_mux_frame_t(*mux_frame);

  if((chassis_issues) != 0){
    if((chassis_issues & BRAKE_FAILURE) != 0){
      set_brake_issue_in_dashboard_light_t(&temp_light, 1);
    }else {
      set_brake_issue_in_dashboard_light_t(&temp_light, 0);
    }
    if((chassis_issues & TIRES_PRESSURE) != 0){
      set_pressure_issue_in_dashboard_light_t(&temp_light, 1);
    }else{
      set_pressure_issue_in_dashboard_light_t(&temp_light, 0);
    }
  }else {
    set_pressure_issue_in_dashboard_light_t(&temp_light, 0);
    set_brake_issue_in_dashboard_light_t(&temp_light, 0);
  }
  if((engine_issues) != 0){
    set_motor_issue_in_dashboard_light_t(&temp_light, 1);
    if((engine_issues & PRESSURE_FAULT) != 0){ //engine_pressure
      set_motor_pressure_in_dashboard_light_t(&temp_light, 1);
    }else{
      set_motor_pressure_in_dashboard_light_t(&temp_light, 0);
    }
    if((engine_issues & COOLANT_TEMPERATURE) != 0){ // cooling
      set_coolant_temperature_in_dashboard_light_t(&temp_light, 1);
    }else {
      set_coolant_temperature_in_dashboard_light_t(&temp_light, 0);
    }
    if((engine_issues & OIL_OVERHEATING) != 0){ // oil_overheat
      set_oil_overheat_in_dashboard_light_t(&temp_light, 1);
    }else {
      set_oil_overheat_in_dashboard_light_t(&temp_light, 0);
    }
  }else {
    set_motor_issue_in_dashboard_light_t(&temp_light, 0);
    set_coolant_temperature_in_dashboard_light_t(&temp_light, 0);
    set_oil_overheat_in_dashboard_light_t(&temp_light, 0);
  }

  if((battery_issues) != 0){
    if((battery_issues & UNLOADED) != 0){
      set_discharged_battery_in_dashboard_light_t(&temp_light, 1);
    }else {
      set_discharged_battery_in_dashboard_light_t(&temp_light, 0);
    }
    if((battery_issues & OUTAGE) != 0){
      set_battery_issue_in_dashboard_light_t(&temp_light, 1);
    }else{
      set_battery_issue_in_dashboard_light_t(&temp_light, 0);
    }
  }else {
    set_battery_issue_in_dashboard_light_t(&temp_light, 0);
    set_discharged_battery_in_dashboard_light_t(&temp_light, 0);
  }

  return temp_light;
}

void decode_comodo_frame(serial_frame_t serial_frame[DRV_MAX_FRAMES], uint32_t data_len, comodo_frame_t comodo_frame[DRV_MAX_FRAMES]){
  for (size_t j = 0; j < data_len; j++) {
    if (serial_frame[j].serNum == SERIAL_COM)
    for (size_t k = 0 ; k < serial_frame[j].frameSize ; k++) {
      if (set_comodo_frame_t(&comodo_frame[j], serial_frame[j].frame[k]) == false) {
        printf("Set comodo frame failed : %s\n", strerror(errno));
      }
    }
  }
}

void decode_bgf_frame(serial_frame_t serial_frame[DRV_MAX_FRAMES], uint32_t data_len, bgf_frame_t bgf_frame[DRV_MAX_FRAMES]){
  for (size_t j = 0; j < data_len; j++) {
    if (serial_frame[j].serNum == SERIAL_BGF){
      uint16_t bgf_frame_temp;
      bgf_frame_temp = serial_frame[j].frame[0];
      bgf_frame_temp = (bgf_frame_temp << 8) | serial_frame[j].frame[1];
      if (set_bgf_frame_t(&bgf_frame[j], bgf_frame_temp) == false) {
        printf("Set bgf frame failed : %s\n", strerror(errno));
      }
    }
  }
}


uint8_t check_crc8(uint8_t *data, size_t length, uint8_t polynomial, uint8_t initial_value){
  uint8_t crc = initial_value;

  for (size_t i = 0; i < length; i++) {
    crc ^= data[i];

    for (uint8_t bit = 0; bit < 8; bit++) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ polynomial;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}