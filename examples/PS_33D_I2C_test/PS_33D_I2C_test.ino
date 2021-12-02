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
    Serial.print("Co2 : ");
    Serial.println(ps_33d_i2c.pressure);
    Serial.println("Status >>");

    switch (cm1106_i2c.status)
    {
    case CM1106_I2C_STATUS_PREHEATING:
    {
      Serial.println("Preheating");
      break;
    }
    case CM1106_I2C_STATUS_NORMAL_OPERATION:
    {
      Serial.println("Normal operation");
      break;
    }
    case CM1106_I2C_STATUS_OPERATING_TROUBLE:
    {
      Serial.println("Operating trouble");
      break;
    }
    case CM1106_I2C_STATUS_OUT_OF_FS:
    {
      Serial.println("Out of FS");
      break;
    }
    case CM1106_I2C_STATUS_NON_CALIBRATED:
    {
      Serial.println("Non calibrated");
      break;
    }
    }
  }
  delay(1000);
}