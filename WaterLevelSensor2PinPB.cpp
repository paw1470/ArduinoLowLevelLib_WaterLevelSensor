#include <Arduino.h>
#include "WaterLevelSensor2PinPB.h"

WaterLevelSensor2PinPB::WaterLevelSensor2PinPB(){
    waterLevel = WaterLevelEnum::WATER_ERROR;
}

void WaterLevelSensor2PinPB::init(uint8_t lowWaterLevelPin, uint8_t highWaterLevelPin, bool useInternalPullUpRes){
    this->lowWaterLevelPin = lowWaterLevelPin;
    this->highWaterLevelPin = highWaterLevelPin;
    if(useInternalPullUpRes){
        pinMode(lowWaterLevelPin, INPUT_PULLUP);
        pinMode(highWaterLevelPin, INPUT_PULLUP);
    } else{
        pinMode(lowWaterLevelPin, INPUT);
        pinMode(highWaterLevelPin, INPUT);
    }
    isWaterLevelChanged();
}

void WaterLevelSensor2PinPB::updateWaterLevel(){
    bool waterSensorLow = isWaterSensorLow();
    bool waterSensorHigh = isWaterSensorHigh();
    if(isWaterLevelEmpty(waterSensorLow, waterSensorHigh)){
        waterLevel = WaterLevelEnum::WATER_LEVEL_EMPTY;
    } else if(isWaterLevelMedium(waterSensorLow, waterSensorHigh)){
        waterLevel = WaterLevelEnum::WATER_LEVEL_MEDIUM;
    } else if(isWaterLevelFull(waterSensorLow, waterSensorHigh)){
        waterLevel = WaterLevelEnum::WATER_LEVEL_FULL;
    } else{
        waterLevel = WaterLevelEnum::WATER_LEVEL_ERROR;
    }
}

bool WaterLevelSensor2PinPB::isWaterLevelChanged(){
    WaterLevelEnum lastWaterLevel = waterLevel;
    updateWaterLevel();
    return lastWaterLevel == waterLevel;
}

WaterLevelEnum WaterLevelSensor2PinPB::getWaterLevel(){
    updateWaterLevel();
    return waterLevel;
}

WaterLevelEnum WaterLevelSensor2PinPB::getLastWaterLevel(){
    return waterLevel;
}

bool WaterLevelSensor2PinPB::isWaterSensorHigh(){
    return !digitalRead(highWaterLevelPin);
}

bool WaterLevelSensor2PinPB::isWaterSensorLow(){
    return !digitalRead(lowWaterLevelPin);
}


bool WaterLevelSensor2PinPB::isWaterLevelLow(bool waterSensorLow, bool waterSensorHigh){
    return isWaterLevelEmpty(waterSensorLow, waterSensorHigh);
}

bool WaterLevelSensor2PinPB::isWaterLevelEmpty(bool waterSensorLow, bool waterSensorHigh){
    return !waterSensorLow & !waterSensorHigh;
}

bool WaterLevelSensor2PinPB::isWaterLevelMedium(bool waterSensorLow, bool waterSensorHigh){
    return waterSensorLow & !waterSensorHigh;
}

bool WaterLevelSensor2PinPB::isWaterLevelHigh(bool waterSensorLow, bool waterSensorHigh){
    return isWaterLevelFull(waterSensorLow, waterSensorHigh);
}

bool WaterLevelSensor2PinPB::isWaterLevelFull(bool waterSensorLow, bool waterSensorHigh){
    return waterSensorLow & waterSensorHigh;
}
bool WaterLevelSensor2PinPB::isWaterLevelError(bool waterSensorLow, bool waterSensorHigh){
    return !waterSensorLow & waterSensorHigh;
}





