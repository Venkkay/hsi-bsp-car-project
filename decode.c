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

  /*if(mux_frame.chassis_issue != NOTHING_CHASSIS){
    if((mux_frame.chassis_issue & 0x1) == TIRES_PRESSURE){
      printf("\nCHASSIS : TIRE PRESSURE\n");
    }
    if((mux_frame.chassis_issue & 0x2) == BRAKE_FAILURE){
      printf("\nCHASSIS : BRAKE ISSUE\n");
    }
  }else {
    printf("\nCHASSIS : NO ISSUE\n");
  }*/

  /*if(mux_frame.engine_issue != NOTHING_ENGINE){
    if((mux_frame.engine_issue & 0x1) == PRESSURE_FAULT){
      printf("\nENGINE : PRESSURE ISSUE\n");
    }
    if((mux_frame.engine_issue & 0x2) == COOLANT_TEMPERATURE){
      printf("\nENGINE : COOLING LIQUID ISSUE\n");
    }
    if((mux_frame.engine_issue & 0x4) == OIL_OVERHEATING){
      printf("\nENGINE : OIL OVERHEATING ISSUE\n");
    }
  }else{
    printf("\nENGINE : NO ISSUE\n");
  }*/

  rpm_t temp_rpm = udpFrame[9];
  temp_rpm = (temp_rpm << 8) | udpFrame[10];
  temp_rpm = (temp_rpm << 8) | udpFrame[11];
  temp_rpm = (temp_rpm << 8) | udpFrame[12];

  /*if(mux_frame.battery_issue != NOTHING_BATTERY){
    if((mux_frame.battery_issue & 0x1) == UNLOADED){
      printf("\nBATTERY : EMPTY BATTERY\n");
    }
    if((mux_frame.battery_issue & 0x2) == OUTAGE){
      printf("\nBATTERY : BATTERY ISSUE\n");
    }
  }else {
    printf("\nBATTERY : NO ISSUE\n");
  }*/

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

void decode_comodo_frame(serial_frame_t serial_frame[DRV_MAX_FRAMES], uint32_t data_len, comodo_frame_t comodo_frame[DRV_MAX_FRAMES]){
  for (size_t j = 0; j < data_len; j++) {
    if(serial_frame[j].serNum == SERIAL_COM)
    for(size_t k = 0 ; k < serial_frame[j].frameSize ; k++) {
      if(set_comodo_frame_t(&comodo_frame[j], serial_frame[j].frame[k]) == false){
        printf("Set mux frame failed : %s\n", strerror(errno));
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