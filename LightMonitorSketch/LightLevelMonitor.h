#ifndef __LIGHT_LEVE_MONITOR_H__
#define __LIGHT_LEVE_MONITOR_H__

#include <stdint.h>


#define	LIGHT_LEVEL_RANGE_SIZE	20


class LightLevelLog;
class LightLevelSensor;
class TimeManager;

class LightLevelMonitor
{
  public:
    LightLevelMonitor(const LightLevelSensor & light_sensor, LightLevelLog & light_log, LightLevelLog & light_history, const TimeManager & time_manager, unsigned update_internal_ms);
    void on_loop();

  private:
    LightLevelLog & _light_log;
	LightLevelLog & _light_history;
	const LightLevelSensor & _light_sensor;
    const TimeManager & _time_manager;
    const unsigned _update_internal_ms;
    uint32_t _last_update_time_ms;
	uint16_t _last_light_level_range;
};



#endif  // __LIGHT_LEVE_MONITOR_H__
