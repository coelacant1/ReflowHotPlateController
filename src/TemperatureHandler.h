#pragma once

#include "MenuStateMachine.h"
#include "PID.h"
#include "ReflowCurves\ReflowCurve.h"
#include "Sensors\TemperatureSensor.h"

class TemperatureHandler{
private:
    const float allowedTempError = 20.0f;
    unsigned long allowedErrorTime = 10000;//ms
    unsigned long errorTime = 0;
    bool errorSet = false;
    TemperatureSensor *tempSensor;
    ReflowCurve *reflowCurve;
    PID pid = PID(1.0f, 0.0f, 0.2f);
    unsigned long currentMillis = 0;
    bool faultDetected = false;


    bool CheckRunaway(float temp, float target){
        if(fabs(temp - target) > allowedTempError){
            if(!errorSet){
                errorSet = true;
                errorTime = millis();
            }
            else if (millis() - errorTime > allowedErrorTime){
                return true;
            }
        }
        else{
            errorSet = false;
        }

        return false;
    }

    bool SendFaultMessage(TemperatureSensor::Fault fault, bool runway = false){
        switch(fault){
            case TemperatureSensor::CJRange:
                MenuStateMachine::PrintMessage("F:CJRange", 3.0f);
                break;
            case TemperatureSensor::THRange:
                MenuStateMachine::PrintMessage("F:THRange", 3.0f);
                break;
            case TemperatureSensor::CJHigh:
                MenuStateMachine::PrintMessage("F:CJHigh", 3.0f);
                break;
            case TemperatureSensor::CJLow:
                MenuStateMachine::PrintMessage("F:CJLow", 3.0f);
                break;
            case TemperatureSensor::THHigh:
                MenuStateMachine::PrintMessage("F:THHigh", 3.0f);
                break;
            case TemperatureSensor::THLow:
                MenuStateMachine::PrintMessage("F:THLow", 3.0f);
                break;
            case TemperatureSensor::Voltage:
                MenuStateMachine::PrintMessage("F:Voltage", 3.0f);
                break;
            case TemperatureSensor::THOpen:
                MenuStateMachine::PrintMessage("F:THOpen", 3.0f);
                break;
            default://None, no message
                break;
        }

        if(runway){
            MenuStateMachine::PrintMessage("F:TH Runway", 3.0f);
        }
    }

    void UpdateMenu(float thermTemp, float coldJTemp, float time, float setPoint){
        MenuStateMachine::SetThermocoupleTemperature(thermTemp);
        MenuStateMachine::SetColdJunctionTemperature(coldJTemp);
        MenuStateMachine::SetTargetTemperature(setPoint);
        MenuStateMachine::SetTime(time);
    }

public:
    TemperatureHandler(TemperatureSensor *tempSensor){
        this->tempSensor = tempSensor;
    }

    void SetReflowCurve(ReflowCurve *reflowCurve){
        this->reflowCurve = reflowCurve;
    }

    void StartTime(){
        currentMillis = millis();
    }

    float GetControl(){
        float thermTemp = tempSensor->GetThermocoupleTemperature();
        float coldJTemp = tempSensor->GetColdJunctionTemperature();
        TemperatureSensor::Fault fault = tempSensor->CheckFaults();

        float time = ((float)(millis() - currentMillis)) / 1000.0f;
        float setPoint = reflowCurve->GetTemperatureAtTime(time);
        float control = pid.Calculate(setPoint, thermTemp);
        bool checkRunaway = CheckRunaway(thermTemp, setPoint);

        UpdateMenu(thermTemp, coldJTemp, time, setPoint);
        SendFaultMessage(fault);

        if (fault != TemperatureSensor::None || faultDetected || checkRunaway){
            control = 0.0f;
            faultDetected = true;
        }

        return control;
    }

};
