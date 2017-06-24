#ifndef __LIGHT_LEVEL_APP_H__
#define __LIGHT_LEVEL_APP_H__


#include "wifi_manager.h"
#include "LightLevelSensor.h"
#include "LightLevelLog.h"
#include "LightLevelMonitor.h"
#include "LightLevelServer.h"
#include "TimeManager.h"


class LightLevelApp
{
  public:
    LightLevelApp(int light_sensor_pin,
                  const char * light_level_log_file_name,
                  unsigned long light_level_update_interval_ms,
                  unsigned long time_manager_update_interval_ms,
                  unsigned web_server_port,
                  const char * wifi_ssid,
                  const char * wifi_password);
    
    void on_setup();
    void on_loop();
    
  private:
    TimeManager _time_manager;
    LightLevelSensor _light_sensor;
    LightLevelLog _light_log;
    LightLevelMonitor _light_monitor;
    LightLevelServer _light_server;
    String _wifi_ssid;
    String _wifi_password;
};


#endif  // __LIGHT_LEVEL_APP_H__
