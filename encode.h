#ifndef ENCODE_H
#define ENCODE_H

#include "drv_api.h"
#include "libs/data_lib/data_management.h"

void bgf_encode_trame(bgf_frame_t* tr, uint8_t id_message, uint8_t message);

#endif //ENCODE_H
