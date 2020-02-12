#include "WaterLevelEnum.h"
#include "WaterLevelSensor2PinPB.h"

#define LOW_PIN 2
#define HIGH_PIN A3     
#define LEVEL_EMPTY_PIN 4
#define LEVEL_MEDIUM_PIN 5
#define LEVEL_FULL_PIN 6
#define LEVEL_ERROR_PIN 13

WaterLevelSensor2PinPB waterLevelSensor;

void setup(){
    waterLevelSensor.init(LOW_PIN, HIGH_PIN, true);
    pinMode(LEVEL_EMPTY_PIN, OUTPUT);
    pinMode(LEVEL_MEDIUM_PIN, OUTPUT);
    pinMode(LEVEL_FULL_PIN, OUTPUT);
    pinMode(LEVEL_ERROR_PIN, OUTPUT);
}

void loop(){
   setLed();
}

void setLed(){
     switch (waterLevelSensor.getWaterLevel()){
    case WATER_LEVEL_EMPTY:
        digitalWrite(LEVEL_EMPTY_PIN, HIGH);
        digitalWrite(LEVEL_MEDIUM_PIN, LOW);
        digitalWrite(LEVEL_FULL_PIN, LOW);
        digitalWrite(LEVEL_ERROR_PIN, LOW);
        break;
    case WATER_LEVEL_MEDIUM:
        digitalWrite(LEVEL_EMPTY_PIN, LOW);
        digitalWrite(LEVEL_MEDIUM_PIN, HIGH);
        digitalWrite(LEVEL_FULL_PIN, LOW);
        digitalWrite(LEVEL_ERROR_PIN, LOW);
        break;
    case WATER_LEVEL_FULL:
        digitalWrite(LEVEL_EMPTY_PIN, LOW);
        digitalWrite(LEVEL_MEDIUM_PIN, LOW);
        digitalWrite(LEVEL_FULL_PIN, HIGH);
        digitalWrite(LEVEL_ERROR_PIN, LOW);
        break;
    case WATER_LEVEL_ERROR:
        digitalWrite(LEVEL_EMPTY_PIN, LOW);
        digitalWrite(LEVEL_MEDIUM_PIN, LOW);
        digitalWrite(LEVEL_FULL_PIN, LOW);
        digitalWrite(LEVEL_ERROR_PIN, HIGH);
        break;
    default:
        break;
    }
}