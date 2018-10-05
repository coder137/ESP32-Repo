#include <Arduino.h>
#include <Wire.h>

#include <WireHelper.h>

void pollRTC();

// Device Registers for DS3231
#define DEVICE_7BIT_ADDR 0x68
#define SEC_REG 0x00
#define DATE_REG 0x04

void setup() 
{
    Serial.begin(9600);
    while(!Serial);

    // NOTE, Begin the Wire
    Serial.printf("Starting Wire\n");
    Wire.begin();

    // NOTE, Write to the DS3231
    wh_setData(DEVICE_7BIT_ADDR, SEC_REG, 3, 0x59, 0x01, 0x02);  // 02:01:00
    wh_setData(DEVICE_7BIT_ADDR, DATE_REG, 3, 0x01, 0x02, 0x03); // 1, Feb, 2003

    // NOTE, Read from the DS3231
    uint8_t secData[3] = {0};
    wh_getData(DEVICE_7BIT_ADDR, SEC_REG, 3, secData);
    Serial.printf("h:m:s %x %x %x\n", secData[2], secData[1], secData[0]);

    Serial.printf("Done\n");
}

void loop() 
{
    // Display the reading here
    pollRTC();
    delay(1000);
}

void pollRTC()
{
    // NOTE, Automatically set to 0
    static uint8_t secData[3];
    static uint8_t dateData[3];
    wh_getData(DEVICE_7BIT_ADDR, SEC_REG, 3, secData);
    wh_getData(DEVICE_7BIT_ADDR, DATE_REG, 3, dateData);
    
    Serial.printf("d:m:y %x %x %x\n", dateData[0], dateData[1], dateData[2]);
    Serial.printf("h:m:s %x %x %x\n", secData[2], secData[1], secData[0]);
    Serial.println("--------------");
}
