#include "TimeManager.h"

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
  _ntp_client.begin();
  on_loop();
}

void TimeManager::on_loop()
{
  unsigned long current_time = millis();
  if (current_time - _last_time_update_ms >= _update_interval_ms)
  {
    _last_time_update_ms = current_time;
    
    // TODO: Only make an NTP call on an NTP update interval.
    time_t new_time = _ntp_client.get_time();
    if (new_time == 0)
    {
      // TODO: Report error.
    }
    else
    {
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
  
  return now();
}

