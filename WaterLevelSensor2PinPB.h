#ifndef WATERLEVELSENSOR2PINPB_H
#define WATERLEVELSENSOR2PINPB_H
#include <inttypes.h>
#include "WaterLevelEnum.h"

//Internal pullup resistor in arduino 10K. Set bool FALSE if you use external betwen VCC and pins. 
//2pin class can return only empty, medium, full and error state
class WaterLevelSensor2PinPB{
    public:
        WaterLevelSensor2PinPB();
        void init(uint8_t lowWaterLevelPin, uint8_t highWaterLevelPin, bool useInternalPullUpRes = true);
        bool isWaterLevelChanged();             //update and return bool
        WaterLevelEnum getWaterLevel();         //update and return
        WaterLevelEnum getLastWaterLevel();     //only return 


    protected:  //ready for inheritance
        WaterLevelEnum  waterLevel;
        uint8_t lowWaterLevelPin;
        uint8_t highWaterLevelPin;

        bool isWaterSensorHigh();
        bool isWaterSensorLow();
        
        void updateWaterLevel();

        bool isWaterLevelEmpty(bool waterSensorLow, bool waterSensorHigh);
        bool isWaterLevelLow(bool waterSensorLow, bool waterSensorHigh);
        bool isWaterLevelMedium(bool waterSensorLow, bool waterSensorHigh);
        bool isWaterLevelHigh(bool waterSensorLow, bool waterSensorHigh);
        bool isWaterLevelFull(bool waterSensorLow, bool waterSensorHigh);
        bool isWaterLevelError(bool waterSensorLow, bool waterSensorHigh);
    
   
};

#endif 