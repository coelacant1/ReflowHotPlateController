#pragma once

#include "..\KeyFrameTrack.h"

class ReflowCurve{
protected:
    KeyFrameTrack setPointControl = KeyFrameTrack(1, 0.0f, 300.0f, 10, KeyFrameTrack::Cosine);
    
public:
    virtual float GetTemperatureAtTime(float seconds) = 0;

};
