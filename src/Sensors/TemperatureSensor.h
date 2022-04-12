#pragma once

#include <Arduino.h>

class TemperatureSensor{
public:
    enum Fault{
        None,
        CJRange,
        THRange,
        CJHigh,
        CJLow,
        THHigh,
        THLow,
        Voltage,
        THOpen
    };

    virtual float GetColdJunctionTemperature() = 0;

    virtual float GetThermocoupleTemperature() = 0;

    virtual Fault CheckFaults() = 0;

};
