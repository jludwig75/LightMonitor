#include "LightLevelApp.h"


LightLevelApp::LightLevelApp(int light_sensor_pin,
                             const char * light_level_log_file_name,
                             unsigned long light_level_update_interval_ms,
                             unsigned long time_manager_update_interval_ms,
                             unsigned web_server_port,
                             const char * wifi_ssid,
                             const char * wifi_password) :
  _time_manager(time_manager_update_interval_ms),
  _light_sensor(light_sensor_pin),
  _light_log(light_level_log_file_name),
  _light_monitor(_light_sensor, _light_log, _time_manager, light_level_update_interval_ms),
  _light_server(web_server_port, _light_sensor, _light_log, "/web_templates"),
  _wifi_ssid(wifi_ssid),
  _wifi_password(wifi_password)
{
}

void LightLevelApp::on_setup()
{
  Serial.begin(115200);

  // Connect to WiFi network
  connect_wifi(_wifi_ssid, _wifi_password);

  _time_manager.on_setup();

  // Start the web server
  _light_server.on_setup();
}

void LightLevelApp::on_loop()
{
  _time_manager.on_loop();
  _light_monitor.on_loop();
  _light_server.on_loop();
}

