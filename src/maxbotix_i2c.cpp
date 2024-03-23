// Library for a Maxbotix I2C ultrasonic rangefinder
#include "maxbotix_i2c.h"

MAXBOTIX_I2C::MAXBOTIX_I2C(TwoWire& i2c_bus) :
i2c_bus_(i2c_bus)
{
}

void MAXBOTIX_I2C::init()
{
    // Start the I2C bus
    i2c_bus_.begin();

    // Return
    return;
}

void MAXBOTIX_I2C::trigger()
{
    // Send the trigger command
    // Should be called no faster than 10 Hz

    if (millis()-t_lastTrigger_ < t_betweenCaptures_)
    {
        last_trigger_success_ = false;
        return;
    }

    // Send the ranging command
    i2c_bus_.beginTransmission(addr_);
    i2c_bus_.write(cmd_range_);
    i2c_bus_.endTransmission();

    t_lastTrigger_ = millis();
    last_trigger_success_ = true;

    // All done
    return;
}

MAXBOTIX_I2C::RESPONSE MAXBOTIX_I2C::read(float* range)
{
    // Reads the latest distance reading and returns if successful

    if (last_trigger_success_ == false)
    {
        return (RESPONSE::TOO_FAST);
    }

    const int n_bytes = 2;

    i2c_bus_.requestFrom(addr_, n_bytes);

    // Read the range if data is available
    if(i2c_bus_.available() >= 2)
    {     
        uint8_t  hi = i2c_bus_.read();        // Read the high byte
        uint8_t  lo = i2c_bus_.read();        // Read the low byte
        uint16_t total = (hi << 8) + lo;      // Convert

        float val = (float) total/100.0f;

        *range = val;     // Convert range to m

        // Value successfully read
        errors_ = 0;

        // Check if the range is out of range
        // Values from datasheet
        if (val < range_min_) return (RESPONSE::TOO_CLOSE);
        if (val > range_max_) return (RESPONSE::TOO_FAR);

        return (RESPONSE::SUCCESS);
    }

    // Reset the bus if it has errored out
    errors_++;

    if (errors_ > 10)
    {
        Serial.print("(Maxbotix) Resetting the I2C bus");
        init();
    }

    // No data was available, return 0
    return (RESPONSE::NO_RESPONSE);

}
