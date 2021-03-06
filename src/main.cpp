#define BYPASSFAULT

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "ButtonHandler.h"
#include "HeaterHandler.h"
#include "TemperatureHandler.h"
#include "ReflowCurves\SMD291AX.h"
#include "ReflowCurves\SMD291SNL.h"
#include "ReflowCurves\SMDLTLFP.h"
#include "Sensors\MAX31856.h"
#include "MenuStateMachine.h"

SMD291AX rCSMD291AX;
SMD291SNL rCSMD291SNL;
SMDLTLFP rCSMDLTLFP;

static const uint8_t curves = 3;
ReflowCurve* reflowCurves[3] = {&rCSMD291AX, &rCSMD291SNL, &rCSMDLTLFP};

MAX31856 tempSensor = MAX31856(10, 11, 12, 13);
TemperatureHandler temp = TemperatureHandler(&tempSensor);
HeaterHandler heater = HeaterHandler(3);
ButtonHandler buttonHandler = ButtonHandler();

uint8_t potentiometer = A0;
uint8_t button = 0;
uint8_t buttonState = 0;
uint8_t page = 0;
uint8_t selection = 0;

void setup() {
    Serial.begin(38400);

    Serial.println("Starting reflow controller...");

    pinMode(potentiometer, INPUT);

    MenuStateMachine::Initialize();
    ButtonHandler::Initialize(button, 2);
}

void loop() {
    bool buttonChange = ButtonHandler::GetValue() != buttonState;

    if(buttonChange){
        if(page == 0){
            page = 1;
        }
        else if(page == 1){
            temp.StartTime();

            page = 2;
        }
        else if(page == 2){
            page = 1;
        }

        buttonState = ButtonHandler::GetValue();
    }
    
    Serial.print("PAGE: ");
    Serial.print(page);
    Serial.print("\tSLCT: ");
    Serial.print(selection);
    Serial.print("\t");

    if(page == 0){
        MenuStateMachine::UpdateDisplay(page, "");
        
        heater.SetControl(0);
        
        Serial.println();
    }
    else if (page == 1){
        selection = map(analogRead(potentiometer), 0, 1023, 0, curves - 1);

        MenuStateMachine::UpdateDisplay(page, reflowCurves[selection]->GetName());

        temp.SetReflowCurve(reflowCurves[selection]);

        heater.SetControl(0);
        
        Serial.println();
    }
    else if (page == 2){
        MenuStateMachine::UpdateDisplay(page, "");

        uint8_t control = temp.GetControl();
        
        heater.SetControl(control);
    }
    else{
        heater.SetControl(0);
    }

    delay(10);
}
