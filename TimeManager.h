#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__


#include "ntp_client.h"


class TimeManager
{
  public:
    TimeManager(uint32_t update_interval_ms);
    uint32_t get_time() const;

    void on_setup();
    void on_loop();
    
  private:
    uint32_t _last_time_update_ms;
    uint32_t _update_interval_ms;
    NtpClient _ntp_client;
};


#endif  // __TIME_MANAGER_H__
