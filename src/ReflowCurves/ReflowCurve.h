#pragma once

#include "..\KeyFrameTrack.h"

class ReflowCurve{
protected:
    KeyFrameTrack setPointControl = KeyFrameTrack(1, 0.0f, 300.0f, 10, KeyFrameTrack::Cosine);
    const String name;

public:
    ReflowCurve(String name) : name(name){}
    
    String GetName(){
        return name;
    }

    virtual float GetTemperatureAtTime(float seconds) = 0;

};
