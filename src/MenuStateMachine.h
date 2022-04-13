#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C_ByVac.h>

class MenuStateMachine{
private:
    static float coldJunctionTemperature;
    static float thermocoupleTemperature;
    static float targetTemperature;
    static float time;
    static unsigned long messageChange;
    static LiquidCrystal_I2C_ByVac lcd;
    static String currentMessage;
    static String topLine;
    static String bottomLine;
    static unsigned long displayUpdate;

    static const String topLineP0;
    static const String botLineP0;
    static const String topLineP1;

    static void WriteToDisplayTop(String message){
        if(message != topLine){
            lcd.clear();
            
            lcd.setCursor(0, 0);
        }
    }
    
    static void WriteToDisplayTop(String message){
        if(message != topLine){
            lcd.clear();
            
            lcd.setCursor(0, 0);
        }
    }

public:
    static void Initialize(){
        messageChange = millis();
        
        lcd.begin(16, 2);
        lcd.autoscroll();
    }

    static void UpdateDisplay(uint8_t page, String selection){
        unsigned long currentTime = millis();

        if(currentTime - displayUpdate > 50){//update every 50ms
            displayUpdate = currentTime;

            if(currentTime < messageChange){
                lcd.clear();
                lcd.setCursor(0, 0);

                for (uint8_t i = 0; i < currentMessage.length(); i++) {
                    lcd.print(currentMessage.charAt(i));
                }
            }
            else if(page == 0){
                lcd.clear();
                lcd.setCursor(0, 0);

                for (uint8_t i = 0; i < topLineP0.length(); i++) {
                    lcd.print(topLineP0.charAt(i));
                }

                lcd.setCursor(0, 1);

                for (uint8_t i = 0; i < botLineP0.length(); i++) {
                    lcd.print(botLineP0.charAt(i));
                }
            }
            else if(page == 1){
                lcd.clear();
                lcd.setCursor(0, 0);

                for (uint8_t i = 0; i < topLineP1.length(); i++) {
                    lcd.print(topLineP1.charAt(i));
                }

                lcd.setCursor(0, 1);

                for (uint8_t i = 0; i < selection.length(); i++) {
                    lcd.print(selection.charAt(i));
                }
            }
            else if(page == 2){
                lcd.clear();
                lcd.setCursor(0, 0);

                for (uint8_t i = 0; i < topLine.length(); i++) {
                    lcd.print(topLine.charAt(i));
                }

                lcd.setCursor(0, 1);

                for (uint8_t i = 0; i < bottomLine.length(); i++) {
                    lcd.print(bottomLine.charAt(i));
                }
            }
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
LiquidCrystal_I2C_ByVac MenuStateMachine::lcd = LiquidCrystal_I2C_ByVac(0x27);
const String MenuStateMachine::topLineP0 = "Heater V1.0";
const String MenuStateMachine::botLineP0 = "Press O to continue...";
const String MenuStateMachine::topLineP1 = "Reflow Curve:";
