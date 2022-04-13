#pragma once

#include "ReflowCurve.h"

class SMD291AX: public ReflowCurve{
private:
    float setPoint;

public:
    SMD291AX() : ReflowCurve("SMD291AX"){
        setPointControl.AddParameter(&setPoint);

        setPointControl.AddKeyFrame(0.0f, 25.0f);
        setPointControl.AddKeyFrame(30.0f, 100.0f);
        setPointControl.AddKeyFrame(120.0f, 150.0f);
        setPointControl.AddKeyFrame(210.0f, 235.0f);
        setPointControl.AddKeyFrame(260.0f, 25.0f);
    }

    float GetTemperatureAtTime(float seconds){
        setPointControl.Update(seconds);
        
        return setPoint;
    }

};
