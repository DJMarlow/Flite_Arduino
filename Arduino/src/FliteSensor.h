/*
    Arduino library for FliteSensor keg sensor

    Author: DJMarlow - https://github.com/DJMarlow
    Date: 2020-7-13
*/

#ifndef FliteSensor_H
#define FliteSensor_H

#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

class FliteSensor {
  public:
    //Sensor current values
    float _level;
    float _psi;
    float _temperature;

    struct raw {
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
    uint8_t convertPressure(const struct raw raw, float *p, const uint16_t oMin, const uint16_t oMax, const float pMin,const float pMax);
    uint8_t convertTemp(const struct raw raw, float *t);
  
};
#endif
