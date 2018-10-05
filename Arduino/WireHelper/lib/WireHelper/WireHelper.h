#ifndef WireHelper_H
#define WireHelper_H

#include <Wire.h>

void wh_setData(uint8_t DEVICE_ADDR, uint8_t REGISTER, int16_t count, ...);
void wh_getData(uint8_t DEVICE_ADDR, uint8_t REG, uint8_t count, uint8_t * ret);

#endif
