#include <ps_33d_i2c.h>

PS_33D_I2C ps_33d_i2c;

void setup()
{
  ps_33d_i2c.begin();
  Serial.begin(9600);
}

void loop()
{
  uint8_t ret = ps_33d_i2c.measure();

  if (ret == 0)
  {
    Serial.print("pressure : ");
    Serial.println(ps_33d_i2c.pressure);

    Serial.print("status (busy) : ");
    switch (ps_33d_i2c.status.busy)
    {
    case PS_33D_I2C_BUSY_SLEEP:
    {
      Serial.println("SLEEP");
      break;
    }
    case PS_33D_I2C_BUSY_ACTIVE:
    {
      Serial.println("ACTIVE");
      break;
    }

    default:
      break;
    }

    Serial.print("status (power) : ");
    switch (ps_33d_i2c.status.power)
    {
    case PS_33D_I2C_POWER_OFF:
    {
      Serial.println("OFF");
      break;
    }
    case PS_33D_I2C_POWER_ON:
    {
      Serial.println("ON");
      break;
    }

    default:
      break;
    }
  }
  delay(1000);
}