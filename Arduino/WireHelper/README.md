# WireHelper

Present in the `lib` folder

Contains two main functions

```c
void wh_setData(uint8_t DEVICE_ADDR, uint8_t REGISTER, int16_t count, ...);
void wh_getData(uint8_t DEVICE_ADDR, uint8_t REG, uint8_t count, uint8_t * ret);
```

### wh_setData

- This function takes in the `7bit DEVICE_ADDR` of the I2C device as well as the `REGISTER` to write to
- count is supplied for the `va_args`
- supply the `uint8_t` data to write to the `REGISTER`

### wh_getData

- This function takes in the `7bit DEVICE_ADDR` of the I2C device as well as the `REGISTER` to read from
- count is supplied for the `Wire.requestFrom` function
- `ret` is a `static uint8_t array[count]`
- **NOTE**: if ret is not static initialize as a 0 array `uint8_t array[count] = {0}`
