#include "FliteSensor.h"

FliteSensor::FliteSensor(char color[10], int EEPROM_distanceLow, int EEPROM_levelLow, int EEPROM_distanceHigh, int EEPROM_levelHigh, int EEPROM_psiZero)
{

    if (strcmp(color, "BLACK") == 0)
    {
        _VL530X_address = 0x30;
        _HSC_address = 0x48;
    }
    else if (strcmp(color, "BLUE") == 0)
    {
        _VL530X_address = 0x31;
        _HSC_address = 0x58;
    }
    else if (strcmp(color, "RED") == 0)
    {
        _VL530X_address = 0x32;
        _HSC_address = 0x68;
    }
    else if (strcmp(color, "GREEN") == 0)
    {
        _VL530X_address = 0x33;
        _HSC_address = 0x78;
    }

    _EEPROM_distanceLow = EEPROM_distanceLow;
    _EEPROM_levelLow = EEPROM_levelLow;
    _EEPROM_distanceHigh = EEPROM_distanceHigh;
    _EEPROM_levelHigh = EEPROM_levelHigh;
    _EEPROM_psiZero = EEPROM_psiZero;
    _level = 0.0;
    _psi = 0.0;
    _temperature = 0;
}

bool FliteSensor::beginSensor()
{
    lox.begin(_VL530X_address);
    return lox.setAddress(_VL530X_address);
}

//Returns the TOF distance in mm
float FliteSensor::getTOFDistance()
{
    float d = 0.0;

    lox.rangingTest(&measure, false);

    //Make sure the status is not 4 (phase failure)
    if (measure.RangeStatus != 4)
    {
        d = measure.RangeMilliMeter;
    }

    return d;
}

//Returns the calculated level
float FliteSensor::getLevel()
{
    float l = 0.0;
    float d = getTOFDistance();

    //If d > 1000 discard reading
    if (d > 1000)
    {
        l = _level;
    }
    else
    {
        //Calculate level based on calibration settings
        float m = (getCalibrationLevelHigh() - getCalibrationLevelLow()) / (getCalibrationDistanceHigh() - getCalibrationDistanceLow());
        float b = getCalibrationLevelHigh() - (m * getCalibrationDistanceHigh());
        l = (m * d) + b;

        //Limit level reading from 0 - 5
        if (l < 0.0)
        {
            l = 0.0;
        }

        if (l > 5.0)
        {
            l = 5.0;
        }

        _level = l;
    }

    return l;
}

uint8_t FliteSensor::getRawPressTemp(const uint8_t slave_addr, struct raw *raw)
{
    Wire.requestFrom(slave_addr, (uint8_t)4);

    uint8_t b1 = Wire.read();
    uint8_t b2 = Wire.read();
    uint8_t b3 = Wire.read();
    uint8_t b4 = Wire.read();

    raw->status = (b1 & 0xc0) >> 6;
    raw->press = ((b1 & 0x3f) << 8) | b2;
    raw->temp = ((b3 << 8) | (b4 & 0xe0)) >> 5;
    if (raw->temp == 65535)
    {
        return 4;
    }
    return raw->status;
}

uint8_t FliteSensor::convertPressure(const struct raw raw, float *p, const uint16_t oMin, const uint16_t oMax, const float pMin, const float pMax)
{
    *p = ((raw.press * 1.0) - oMin) * (pMax - pMin) / (oMax - oMin) + pMin;
    return 0;
}

uint8_t FliteSensor::convertTemp(const struct raw raw, float *t)
{
    *t = ((raw.temp / 2047.0) * 200) - 50;
    return 0;
}

//Get the raw pressure
float FliteSensor::getRawPressure()
{
    struct raw ps;
    uint8_t __attribute__((unused)) status;
    float p = -1;
    status = getRawPressTemp(_HSC_address, &ps);
    convertPressure(ps, &p, 0x666, 0x399A, 0.0, 150.0);

    return p;
}

//Get the corrected pressure based on zero cal
float FliteSensor::getPressure()
{
    float p = 0.0;

    p = getRawPressure() - getCalibrationZeroPSI();

    _psi = p;

    return p;
}

float FliteSensor::getTemperature()
{
    struct raw ps;
    uint8_t __attribute__((unused)) status;
    float t = -1;
    status = getRawPressTemp(_HSC_address, &ps);
    convertTemp(ps, &t);

    t = (t * 9 / 5) + 32;

    _temperature = t;

    return t;
}

//Called for low calibration point
void FliteSensor::calibrateLow(float l)
{
    //Store the current distance value in memory
    setCalibrationDistanceLow(getTOFDistance());
    delay(1000);

    //Store the currently calibrated level in memory
    setCalibrationLevelLow(l);
}

void FliteSensor::setCalibrationDistanceLow(float d)
{
    //Store this distance value in memory
    EEPROM.put(_EEPROM_distanceLow, d);
    EEPROM.commit();
    delay(1000);
}

float FliteSensor::getCalibrationDistanceLow()
{
    float d = 0.0;
    EEPROM.get(_EEPROM_distanceLow, d);
    //If d is null initialize cal distance at 600 mm away
    if (isnan(d))
    {
        d = 600.0;
    }
    return d;
}

void FliteSensor::setCalibrationLevelLow(float l)
{
    //Store this level value in memory
    EEPROM.put(_EEPROM_levelLow, l);
    EEPROM.commit();
    delay(1000);
}

float FliteSensor::getCalibrationLevelLow()
{
    float l = 0.0;
    EEPROM.get(_EEPROM_levelLow, l);
    //If level is null initialize level at 0
    if (isnan(l))
    {
        l = 0.0;
    }
    return l;
}

//Called for high calibration point
void FliteSensor::calibrateHigh(float l)
{
    //Store the current distance value in memory
    setCalibrationDistanceHigh(getTOFDistance());
    delay(1000);

    //Store the currently calibrated level in memory
    setCalibrationLevelHigh(l);
}

void FliteSensor::setCalibrationDistanceHigh(float d)
{
    //Store this distance value in memory
    EEPROM.put(_EEPROM_distanceHigh, d);
    EEPROM.commit();
    delay(1000);
}

float FliteSensor::getCalibrationDistanceHigh()
{
    float d = 0.0;
    EEPROM.get(_EEPROM_distanceHigh, d);
    //If d is null initialize cal distance at 100 mm away
    if (isnan(d))
    {
        d = 100.0;
    }
    return d;
}

void FliteSensor::setCalibrationLevelHigh(float l)
{
    //Store this level value in memory
    EEPROM.put(_EEPROM_levelHigh, l);
    EEPROM.commit();
    delay(1000);
}

float FliteSensor::getCalibrationLevelHigh()
{
    float l = 0.0;
    EEPROM.get(_EEPROM_levelHigh, l);
    //If l is null initialize level at 5
    if (isnan(l))
    {
        l = 5.0;
    }
    return l;
}

void FliteSensor::calibrateZeroPSI()
{
    //Store the current pressure value in memory
    setCalibrationZeroPSI(getRawPressure());
    delay(1000);
}

void FliteSensor::setCalibrationZeroPSI(float p)
{
    //Store this pressure value in memory
    EEPROM.put(_EEPROM_psiZero, p);
    EEPROM.commit();
    delay(1000);
}

float FliteSensor::getCalibrationZeroPSI()
{
    float p = 0.0;
    EEPROM.get(_EEPROM_psiZero, p);
    //If l is null initialize pressure at 0
    if (isnan(p))
    {
        p = 0.0;
    }
    return p;
}
