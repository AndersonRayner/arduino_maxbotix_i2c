#include <Arduino.h>
#include <Wire.h>

#include <maxbotix_i2c.h>

MAXBOTIX_I2C rangefinder(Wire);


void setup()
{
    Serial.begin(115200);  // Debug serial over USB at 115200 baud

    // Initialize the I2C sensors and ping them
    rangefinder.init();

}

void loop()
{
    // Get readings from all sensors
    float range;
    bool success;

    rangefinder.trigger();
    delay(200);
    
    success = rangefinder.read(&range);

    if (success)
    {
        Serial.printf("Range: %.2f [ m ]\n",range);
    }
    else
    {
        Serial.printf("Sensor read unsuccessful\n");
    }
    
    delay(50);

}
