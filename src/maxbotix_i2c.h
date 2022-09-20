// Maxbotix I2C Driver for Arduino
// Apparnently might need a pull up on SDA/SCL to work reliably...

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

class MAXBOTIX_I2C {
    public :
        MAXBOTIX_I2C(TwoWire& i2c_bus);

        // === Functions
        void init();
        void trigger();
        bool read(float* range);
		
		uint32_t t_last() { return (t_last_); }

        // === Debugging
        uint8_t _debug = 0;
        
    private:
        TwoWire& i2c_bus_;

        const int addr_ = 0x70;     // 7-bit address

        // Commands
        const int cmd_range_ = 0x51;

        // Other
        uint32_t t_update_ = 0;     // Time last capture was commanded [ ms ]
        uint32_t t_capture_ = 100;  // Time between captures [ ms ]
        float range_ = 0.0f;        // Last read range [ m ]
        int errors_ = 0;            // Number of errors

        
};