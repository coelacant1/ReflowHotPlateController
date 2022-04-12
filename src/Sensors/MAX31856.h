#pragma once

#include "TemperatureSensor.h"
#include <Adafruit_MAX31856.h>

class MAX31856 : public TemperatureSensor{
private:
    Adafruit_MAX31856 maxthermo;

public:
    MAX31856(uint8_t CS, uint8_t DI, uint8_t DO, uint8_t CLK) : maxthermo(Adafruit_MAX31856(CS, DI, DO, CLK)){
        
        maxthermo.begin();

        maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);

        maxthermo.setColdJunctionFaultThreshholds(15.0f, 35.0f);

        maxthermo.setTempFaultThreshholds(15.0f, 325.0f);
    }

    float GetColdJunctionTemperature(){
        return maxthermo.readCJTemperature();
    }

    float GetThermocoupleTemperature(){
        return maxthermo.readThermocoupleTemperature();
    }

    Fault CheckFaults(){
        // Check and print any faults
        uint8_t fault = maxthermo.readFault();

        if (fault) {
            if (fault & MAX31856_FAULT_CJRANGE) return CJRange;
            if (fault & MAX31856_FAULT_TCRANGE) return THRange;
            if (fault & MAX31856_FAULT_CJHIGH)  return CJHigh;
            if (fault & MAX31856_FAULT_CJLOW)   return CJLow;
            if (fault & MAX31856_FAULT_TCHIGH)  return THHigh;
            if (fault & MAX31856_FAULT_TCLOW)   return THLow;
            if (fault & MAX31856_FAULT_OVUV)    return Voltage;
            if (fault & MAX31856_FAULT_OPEN)    return THOpen;
        }

        return None;
    }
};
