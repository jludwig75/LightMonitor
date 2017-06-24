#ifndef __LIGHT_LEVE_MONITOR_H__
#define __LIGHT_LEVE_MONITOR_H__


class LightLevelLog;
class LightLevelSensor;
class TimeManager;

class LightLevelMonitor
{
  public:
    LightLevelMonitor(const LightLevelSensor & light_sensor, LightLevelLog & light_log, const TimeManager & time_manager, unsigned update_internal_ms);
    void on_loop();

  private:
    LightLevelLog & _light_log;
    const LightLevelSensor & _light_sensor;
    const TimeManager & _time_manager;
    const unsigned _update_internal_ms;
    unsigned _last_update_time_ms;
};



#endif  // __LIGHT_LEVE_MONITOR_H__
