#pragma once

#include "ReflowCurve.h"

class SMDLTLFP: public ReflowCurve{
private:
    float setPoint;

public:
    SMDLTLFP() : ReflowCurve("SMDLTLFP"){
        setPointControl.AddParameter(&setPoint);

        setPointControl.AddKeyFrame(0.0f, 25.0f);
        setPointControl.AddKeyFrame(90.0f, 90.0f);
        setPointControl.AddKeyFrame(180.0f, 130.0f);
        setPointControl.AddKeyFrame(240.0f, 165.0f);
        setPointControl.AddKeyFrame(290.0f, 25.0f);

    }

    float GetTemperatureAtTime(float seconds){
        setPointControl.SetCurrentTime(seconds);
        
        return setPoint;
    }

};
