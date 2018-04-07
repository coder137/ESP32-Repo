# Configurations

**NOTE: Make sure in the `make menuconfig` you set Component Config -> FreeRTOS to -> Run on first core**

> Added this in make menuconfig already

1. blink
	* Demo ESP-IDF Blink code modified slightly

2. blinkAndPrint
	* Built on `1`
	* Added a freeRTOS print parameter for greater debug facility

3. freertosStyle
	* Built on `2`
	* Added function prototypes on the top like freeRTOS (refer to Book)

4. barebones
	* Modified to give the absolute bare essentials to get started with coding the ESP32
