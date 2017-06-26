#include "LightLevelSensor.h"

#include <Arduino.h>


LightLevelSensor::LightLevelSensor(int light_sensor_pin) : _light_sensor_pin(light_sensor_pin)
{
}

int LightLevelSensor::get_current_light_level() const
{
  return analogRead(_light_sensor_pin);
}

