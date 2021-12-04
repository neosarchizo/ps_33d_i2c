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
    Serial.print("status : ");
    Serial.println(ps_33d_i2c.status);
  }
  delay(1000);
}