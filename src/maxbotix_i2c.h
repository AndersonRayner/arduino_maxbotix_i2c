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
		
		uint32_t lastTrigger() { return (t_lastTrigger_); }
        uint32_t tWait() { return (t_betweenCaptures_); }

        // === Debugging
        uint8_t _debug = 0;
        
    private:
        TwoWire& i2c_bus_;

        // Commands
        const int addr_ = 0x70;     // 7-bit address
        const int cmd_range_ = 0x51;

        // Constants
        const float range_min_ = 0.21;  // Minimum measurable range in [ m ]
        const float range_max_ = 6.50;  // Maximum measurable range in [ m ]  

        // Other
        uint32_t t_lastTrigger_ = 0;     // Time last capture was commanded [ ms ]
        uint32_t t_betweenCaptures_ = 100;  // Time between captures [ ms ]
        float range_ = 0.0f;        // Last read range [ m ]
        int errors_ = 0;            // Number of errors

        
};
