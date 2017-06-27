#include "TimeManager.h"

#include "tracing.h"
#include <Arduino.h>
#include <Time.h>
#include <TimeLib.h>
#include "ntp_client.h"


TimeManager::TimeManager(uint32_t update_interval_ms) :
  _last_time_update_ms(0),
  _update_interval_ms(update_interval_ms),
  _ntp_client()
{
}

void TimeManager::on_setup()
{
  inf_printf("Starting time manager\n");

  inf_printf("Starting NTP client...\n");
  _ntp_client.begin();
  on_loop();
}

void TimeManager::on_loop()
{
  unsigned long current_time = millis();
  if (_last_time_update_ms == 0 || current_time - _last_time_update_ms >= _update_interval_ms)
  {
    _last_time_update_ms = current_time;

    inf_printf("Updating time via NTP...\n");
    
    // TODO: Only make an NTP call on an NTP update interval.
    time_t new_time = _ntp_client.get_time();
    if (new_time == 0)
    {
      // TODO: Report error.
      err_printf("Failed to update time via NTP.\n");
    }
    else
    {
      inf_printf("Updated time via NTP to %lu.\n", new_time);
      setTime(new_time);
    }
  }  
}

uint32_t TimeManager::get_time() const
{
  if (_last_time_update_ms == 0)
  {
    const_cast<TimeManager *>(this)->on_loop();
  }
  
  return (uint32_t)now();
}

