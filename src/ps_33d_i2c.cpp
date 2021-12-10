/*
ps_33d_i2c.cpp -- Arduino library to control Blue Sky PS-33D I2C

Copyright (c) 2018 Neosarchizo.
All rights reserved.

This file is part of the library PS-33D I2C.

PS-33D I2C is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PS-33D I2C is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "ps_33d_i2c.h"

/**
 * Start PS-33D I2C library
 */
void PS_33D_I2C::begin(TwoWire &wirePort)
{
    _i2cPort = &wirePort; // Grab which port the user wants us to use

    // We expect caller to begin their I2C port, with the speed of their choice external to the library
    // But if they forget, we start the hardware here.
    _i2cPort->begin();
}

/**
 * Read result of measuring
 * @return {@code 0} Reading PM2008 value succeeded
 *         {@code 1} Buffer(index) is short
 */
uint8_t PS_33D_I2C::measure()
{
    _i2cPort->beginTransmission(PS_33D_I2C_ADDRESS);
    _i2cPort->write(PS_33D_I2C_CMD_MEASURE);
    _i2cPort->endTransmission();
    delay(PS_33D_I2C_DELAY_FOR_ACK);
    _i2cPort->requestFrom(PS_33D_I2C_ADDRESS, 4);
    uint8_t idx = 0;

    while (_i2cPort->available())
    { // slave may send less than requested
        uint8_t b = _i2cPort->read();
        _buffer[idx++] = b;
        if (idx == 4)
            break;
    }

    if (idx < 4)
    {
#ifdef PS_33D_DEBUG
        Serial.println("PS_33D_I2C::measure_result : buffer is short!");
#endif
        return 1;
    }

    uint32_t adc_val = (_buffer[1] << 16) + (_buffer[2] << 8) + _buffer[3];

    pressure = (adc_val - 0x800000) * (0x07d0) / (0xb33333);

    /// Status
    status = {_buffer[0]};

    return 0;
}
