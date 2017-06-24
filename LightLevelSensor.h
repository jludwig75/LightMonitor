#ifndef __LIGHT_LEVEL_SENSOR_H__
#define __LIGHT_LEVEL_SENSOR_H__


class LightLevelSensor
{
  public:
    LightLevelSensor(int light_sensor_pin);
    int get_current_light_level() const;
    
  private:
    int _light_sensor_pin;
};



#endif // __LIGHT_LEVEL_SENSOR_H__
