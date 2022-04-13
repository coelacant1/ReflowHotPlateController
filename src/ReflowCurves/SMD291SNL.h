#pragma once

#include "ReflowCurve.h"

class SMD291SNL: public ReflowCurve{
private:
    float setPoint;

public:
    SMD291SNL() : ReflowCurve("SMD291SNL"){
        setPointControl.AddParameter(&setPoint);

        setPointControl.AddKeyFrame(0.0f, 25.0f);
        setPointControl.AddKeyFrame(90.0f, 150.0f);
        setPointControl.AddKeyFrame(180.0f, 175.0f);
        setPointControl.AddKeyFrame(240.0f, 249.0f);
        setPointControl.AddKeyFrame(290.0f, 25.0f);

    }

    float GetTemperatureAtTime(float seconds){
        setPointControl.SetCurrentTime(seconds);
        
        return setPoint;
    }

};
