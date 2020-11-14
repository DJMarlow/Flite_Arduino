/*
    Arduino library for Flite keg sensor

    **Hardware Documentation
    Pressure Temperature Sensor I2C Documentation - https://sensing.honeywell.com/i2c-comms-digital-output-pressure-sensors-tn-008201-3-en-final-30may12.pdf
    Distance Sensor API Documentation - https://www.st.com/en/embedded-software/stsw-img005.html

    **This library was developed using the below library developed by Adafruit
    Adafruit VL53L0X Documentation - https://github.com/adafruit/Adafruit_VL53L0X

    Author: DJMarlow - https://github.com/DJMarlow
    Date: 2020-8-25
    Version 1.0.0
    
    MIT License

    Copyright (c) 2020 Derrick Marlow

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef FliteSensor_H
#define FliteSensor_H

#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

class FliteSensor
{
public:
    //Sensor current values
    float _level;
    float _psi;
    float _temperature;

    struct raw
    {
        uint8_t status;
        uint16_t press;
        uint16_t temp;
    };

    //Sensor objects
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();
    VL53L0X_RangingMeasurementData_t measure;

    //Memory locations
    int _EEPROM_distanceLow;
    int _EEPROM_levelLow;
    int _EEPROM_distanceHigh;
    int _EEPROM_levelHigh;
    int _EEPROM_psiZero;

    //Construct keg sensor with individual sensor addresses and memory locations
    FliteSensor(char color[10], int EEPROM_distanceLow, int EEPROM_levelLow, int EEPROM_distanceHigh, int EEPROM_levelHigh, int EEPROM_psiZero);

    //Public functions
    bool beginSensor();
    float getTOFDistance();
    float getLevel();
    float getPressure();
    float getTemperature();
    void calibrateLow(float l);
    void setCalibrationDistanceLow(float d);
    float getCalibrationDistanceLow();
    void setCalibrationLevelLow(float l);
    float getCalibrationLevelLow();
    void calibrateHigh(float l);
    void setCalibrationDistanceHigh(float d);
    float getCalibrationDistanceHigh();
    void setCalibrationLevelHigh(float l);
    float getCalibrationLevelHigh();
    void calibrateZeroPSI();
    void setCalibrationZeroPSI(float p);
    float getCalibrationZeroPSI();

private:
    //Sensor addresses
    int _VL530X_address;
    int _HSC_address;

    //Functions
    float getRawPressure();
    uint8_t getRawPressTemp(const uint8_t slave_addr, struct raw *raw);
    uint8_t convertPressure(const struct raw raw, float *p, const uint16_t oMin, const uint16_t oMax, const float pMin, const float pMax);
    uint8_t convertTemp(const struct raw raw, float *t);
};
#endif
