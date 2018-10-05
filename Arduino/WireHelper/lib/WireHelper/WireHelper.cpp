# include "WireHelper.h"

//Works
void wh_setData(uint8_t DEVICE_ADDR, uint8_t REGISTER, int16_t count, ...)
{
	va_list argument;
	va_start(argument, count);

	Wire.beginTransmission(DEVICE_ADDR);
	Wire.write(REGISTER);
	for(int i=0;i<count;i++)
	{
		//NOTE, int and double are the only values we can take
		uint8_t arg = (uint8_t) va_arg(argument, int);
		Wire.write(arg);
		// Serial.printf("Write %d: %d\n",i, arg);
	}
	Wire.endTransmission();
	va_end(argument);
}

void wh_getData(uint8_t DEVICE_ADDR, uint8_t REG, uint8_t count, uint8_t * ret)
{
	//DS3231 has 19 registers
	//uint8_t * ret = (uint8_t *) malloc(count * sizeof(uint8_t));

	Wire.beginTransmission(DEVICE_ADDR);
	Wire.write(REG);
	Wire.endTransmission();
	Wire.requestFrom(DEVICE_ADDR, count);
	for(int i=0;i<count;i++)
	{
		ret[i] = Wire.read();
	}
}
