/*
ps_33d_i2c.h -- Arduino library to control Blue Sky PS-33D I2C

Copyright (c) 2019 Neosarchizo.
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

#ifndef _PS_33D_I2C_h
#define _PS_33D_I2C_h

#include <Arduino.h>
#include <Wire.h>

#define PS_33D_I2C_ADDRESS 0x4C

// Commands
#define PS_33D_I2C_CMD_MEASURE 0xAA

#define PS_33D_I2C_DELAY_FOR_ACK 10

// #define PS_33D_DEBUG

class PS_33D_I2C
{

public:
  void begin(TwoWire &wirePort = Wire); //By default use Wire port
  uint8_t measure;
  
  uint8_t status;
  uint32_t pressure;

private:
  uint8_t _buffer[32];
  TwoWire *_i2cPort; //The generic connection to user's chosen I2C hardware
};

#endif
