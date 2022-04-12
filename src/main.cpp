#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "HeaterHandler.h"
#include "TemperatureHandler.h"
#include "ReflowCurves\SMD291AX.h"
#include "Sensors\MAX31856.h"
#include "MenuStateMachine.h"

SMD291AX reflowCurve;
MAX31856 tempSensor = MAX31856(10, 11, 12, 13);
TemperatureHandler temp = TemperatureHandler(&tempSensor);
HeaterHandler heater = HeaterHandler(2);
uint8_t potentiometer = A0;
uint8_t button = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("Starting reflow controller...");

  MenuStateMachine::Initialize(potentiometer, button);

  temp.SetReflowCurve(&reflowCurve);
}

void loop() {

  MenuStateMachine::UpdateDisplay();

  // finish menu state machine
  // figure out switching between current mode, from menu
  // drive output to heater based on temperature handler
  // update display from menu state machine


}
