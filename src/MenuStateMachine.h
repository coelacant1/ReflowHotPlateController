#pragma once

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

class MenuStateMachine{
private:
    static float coldJunctionTemperature;
    static float thermocoupleTemperature;
    static float targetTemperature;
    static float time;
    static uint8_t control;
    static unsigned long messageChange;
    static LiquidCrystal_I2C lcd;
    static String currentMessage;
    static String topLine;
    static String bottomLine;
    static unsigned long displayUpdate;

    static const String topLineP0;
    static const String botLineP0;
    static const String topLineP1;

    static String reflowProfile;

    static void WriteToDisplayTop(String message){
        if(message != topLine){
            //lcd.clear();
            lcd.setCursor(0, 0);

            for (uint8_t i = 0; i < message.length(); i++) {
                lcd.print(message.charAt(i));
            }

            for (uint8_t i = message.length(); i < 16; i++) {
                lcd.print(' ');
            }

            topLine = message;
        }
    }
    
    static void WriteToDisplayBot(String message){
        if(message != bottomLine){
            //lcd.clear();
            lcd.setCursor(0, 1);

            for (uint8_t i = 0; i < message.length(); i++) {
                lcd.print(message.charAt(i));
            }

            for (uint8_t i = message.length(); i < 16; i++) {
                lcd.print(' ');
            }

            bottomLine = message;
        }
    }

public:
    static void Initialize(){
        messageChange = millis();
        displayUpdate = millis();
        
        lcd.init();
        lcd.init();

        lcd.backlight();
        lcd.noBlink();
        //lcd.noCursor();
        //lcd.autoscroll();
    }

    static void UpdateDisplay(uint8_t page, String selection){
        unsigned long currentTime = millis();
        

        if(currentTime - displayUpdate > 50){//update every 100ms
            displayUpdate = currentTime;

            if(currentTime < messageChange){
                WriteToDisplayTop(currentMessage);
                WriteToDisplayBot("Error.");
            }
            else if(page == 0){
                WriteToDisplayTop(topLineP0);
                WriteToDisplayBot(botLineP0);
            }
            else if(page == 1){
                WriteToDisplayTop(topLineP1);
                WriteToDisplayBot(selection);

                reflowProfile = selection;
            }
            else if(page == 2){//temps, time, etc
                String topData, botData;

                if((currentTime / 2500) % 2){
                    topData = "TH:" + String(thermocoupleTemperature, 1) + " SP:" + String(targetTemperature, 1);
                }
                else{
                    topData = "CJ:" + String(coldJunctionTemperature, 1) + " CT:" + String(control);
                }

                botData = "T:" + String(time, 1) + " RF:" + reflowProfile.substring((currentTime / 1000) % 6);

                WriteToDisplayTop(topData);
                WriteToDisplayBot(botData);
            }
        }
    }

    static void SetThermocoupleTemperature(float temperature){
        MenuStateMachine::thermocoupleTemperature = temperature;
    }

    static void SetColdJunctionTemperature(float temperature){
        MenuStateMachine::coldJunctionTemperature = temperature;
    }

    static void SetTargetTemperature(float temperature){
        MenuStateMachine::targetTemperature = temperature;
    }

    static void SetTime(float time){
        MenuStateMachine::time = time;
    }

    static void SetControl(uint8_t control){
        MenuStateMachine::control = control;
    }

    static void PrintMessage(String message, float messageTime){
        MenuStateMachine::currentMessage = message;
        MenuStateMachine::messageChange = millis() + (unsigned long)(messageTime * 1000.0f);
    }

};

float MenuStateMachine::coldJunctionTemperature = 0;
float MenuStateMachine::thermocoupleTemperature = 0;
float MenuStateMachine::targetTemperature = 0;
float MenuStateMachine::time = 0;
uint8_t MenuStateMachine::control = 0;
unsigned long MenuStateMachine::messageChange = 0;
LiquidCrystal_I2C MenuStateMachine::lcd = LiquidCrystal_I2C(0x27, 16, 2);
String MenuStateMachine::currentMessage = "";
String MenuStateMachine::topLine = "";
String MenuStateMachine::bottomLine = "";
unsigned long MenuStateMachine::displayUpdate = 0;
String MenuStateMachine::reflowProfile = "";

const String MenuStateMachine::topLineP0 = "Heater V1.0";
const String MenuStateMachine::botLineP0 = "Press O to continue...";
const String MenuStateMachine::topLineP1 = "Reflow Curve:";