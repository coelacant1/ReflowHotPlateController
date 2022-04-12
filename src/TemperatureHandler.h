#pragma once

#include "MenuStateMachine.h"
#include "PID.h"
#include "ReflowCurves\ReflowCurve.h"
#include "Sensors\TemperatureSensor.h"

class TemperatureHandler{
private:
    TemperatureSensor *tempSensor;
    ReflowCurve *reflowCurve;
    PID pid = PID(1.0f, 0.0f, 0.2f);
    unsigned long currentMillis = 0;
    bool faultDetected = false;

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

    bool SendFaultMessage(TemperatureSensor::Fault fault){
        switch(fault){
            case TemperatureSensor::CJRange:
                MenuStateMachine::PrintMessage("Cold Junction Range Fault", 3.0f);
                break;
            case TemperatureSensor::THRange:
                MenuStateMachine::PrintMessage("Thermocouple Range Fault", 3.0f);
                break;
            case TemperatureSensor::CJHigh:
                MenuStateMachine::PrintMessage("Cold Junction High Fault", 3.0f);
                break;
            case TemperatureSensor::CJLow:
                MenuStateMachine::PrintMessage("Cold Junction Low Fault", 3.0f);
                break;
            case TemperatureSensor::THHigh:
                MenuStateMachine::PrintMessage("Thermocouple High Fault", 3.0f);
                break;
            case TemperatureSensor::THLow:
                MenuStateMachine::PrintMessage("Thermocouple Low Fault", 3.0f);
                break;
            case TemperatureSensor::Voltage:
                MenuStateMachine::PrintMessage("Over/Under Voltage Fault", 3.0f);
                break;
            case TemperatureSensor::THOpen:
                MenuStateMachine::PrintMessage("Thermocouple Open Fault", 3.0f);
                break;
            default://None, no message
                break;
        }
    }

    void UpdateMenu(float thermTemp, float coldJTemp, float time, float setPoint){
        MenuStateMachine::SetThermocoupleTemperature(thermTemp);
        MenuStateMachine::SetColdJunctionTemperature(coldJTemp);
        MenuStateMachine::SetTargetTemperature(setPoint);
        MenuStateMachine::SetTime(time);
    }
    
    float GetControl(){
        float thermTemp = tempSensor->GetThermocoupleTemperature();
        float coldJTemp = tempSensor->GetColdJunctionTemperature();
        TemperatureSensor::Fault fault = tempSensor->CheckFaults();

        float time = ((float)(millis() - currentMillis)) / 1000.0f;
        float setPoint = reflowCurve->GetTemperatureAtTime(time);
        float control = pid.Calculate(setPoint, thermTemp);

        UpdateMenu(thermTemp, coldJTemp, time, setPoint);
        SendFaultMessage(fault);

        if (fault != TemperatureSensor::None || faultDetected){
            control = 0.0f;
            faultDetected = true;
        }

        return control;
    }

};
