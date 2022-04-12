#pragma once

#include <Arduino.h>
#include "ButtonHandler.h"

class MenuStateMachine{
private:
    static float coldJunctionTemperature;
    static float thermocoupleTemperature;
    static float targetTemperature;
    static float time;
    static uint8_t potentiometerPin;
    static ButtonHandler buttonHandler;
    static unsigned long messageChange;
    static String currentMessage;


public:
    static void Initialize(uint8_t potentiometerPin, uint8_t buttonPin){
        messageChange = millis();

        buttonHandler.Initialize(buttonPin, 3);

        pinMode(potentiometerPin, INPUT);
    }

    static void UpdateDisplay(){
        if(millis() < messageChange){
            //PRINT MESSAGE
            //Limit size
        }
        else{

        }

    }

    static float SetThermocoupleTemperature(float temperature){
        MenuStateMachine::thermocoupleTemperature = temperature;
    }

    static float SetColdJunctionTemperature(float temperature){
        MenuStateMachine::coldJunctionTemperature = temperature;
    }

    static float SetTargetTemperature(float temperature){
        MenuStateMachine::targetTemperature = temperature;
    }

    static float SetTime(float time){
        MenuStateMachine::time = time;
    }

    static void PrintMessage(String message, float messageTime){
        MenuStateMachine::currentMessage = message;
        MenuStateMachine::messageChange = millis() + (unsigned long)(messageTime * 1000.0f);
    }

};

unsigned long MenuStateMachine::messageChange = 0;
