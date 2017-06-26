#include "LightLevelMonitor.h"

#include "LightLevelSensor.h"
#include "LightLevelLog.h"
#include "TimeManager.h"

#include "tracing.h"
#include <Arduino.h>


LightLevelMonitor::LightLevelMonitor(const LightLevelSensor & light_sensor, LightLevelLog & light_log, const TimeManager & time_manager, unsigned update_internal_ms) :
  _light_log(light_log),
  _light_sensor(light_sensor),
  _time_manager(time_manager),
  _update_internal_ms(update_internal_ms),
  _last_update_time_ms(0)
{
}

void LightLevelMonitor::on_loop()
{
  unsigned long current_time = millis();
  if (current_time - _last_update_time_ms >= _update_internal_ms)
  {
    _last_update_time_ms = current_time;

    inf_printf("Getting current time\n");
    uint32_t current_time = _time_manager.get_time();
    uint16_t light_level = _light_sensor.get_current_light_level();

    inf_printf("Logging light level %u at %lu\n", light_level, current_time);
    _light_log.log_light_level(current_time, light_level);
  }
}
