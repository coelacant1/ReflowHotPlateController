//PULLED FROM https://github.com/coelacant1/ProtoTracer
#pragma once

#include <Arduino.h>

class PID {
private:
	float integral = 0.0f;
	float error = 0.0f;
	float previousError = 0.0f;
	float output = 0.0f;
	float kp = 1.0f;
	float ki = 0.0f;
	float kd = 0.0f;
    unsigned long previousMillis = 0;

public:
	PID() {
        previousMillis = millis();
    }

	~PID();

	PID(float kp, float ki, float kd){
        this->kp = kp;
        this->ki = ki;
        this->kd = kd;

        previousMillis = millis();
    }

	float Calculate(float setpoint, float processVariable){
        float POut, IOut, DOut;

        unsigned long currentMillis = millis();
        float dT = ((float)(currentMillis - previousMillis)) / 1000.0f;

        error = setpoint - processVariable;
        integral += error * dT;

        POut = kp * error;
        IOut = ki * integral;
        DOut = kd * ((error - previousError) / dT);

        output = POut + IOut + DOut;
        previousError = error;
        
        previousMillis = currentMillis;

        return output;
    }
};
