#pragma once

#include <Arduino.h>

class HeaterHandler{
private:
    uint8_t pin = 0;

public:
    HeaterHandler(uint8_t pin){
        this->pin = pin;

        pinMode(pin, OUTPUT);
    }

    void SetControl(uint8_t control){
        analogWrite(pin, control);
    }
};
