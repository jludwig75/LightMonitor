#include "LightLevelServer.h"

#include "LightLevelSensor.h"


LightLevelServer::LightLevelServer(int server_port, LightLevelSensor & light_level_sensor, LightLevelLog & light_log, const String & templates_base_dir) :
 OOWebServer<LightLevelServer>(templates_base_dir, server_port),
 _light_level_sensor(light_level_sensor),
 _light_log(light_log)
{
}

void LightLevelServer::on_setup()
{
  begin();
}

void LightLevelServer::on_loop()
{
  handleClient();
}

void LightLevelServer::server_begin()
{
  on("/", &LightLevelServer::handle_root);
  on("/light_level", &LightLevelServer::handle_light_level);
  on("/light_history", &LightLevelServer::handle_light_level_history);
}

void LightLevelServer::handle_root() {
  send(200, "text/plain", "Hello from the esp8266 web server.");
}

void LightLevelServer::handle_light_level() {
  send(200, "text/plain", String("Light level = ") + _light_level_sensor.get_current_light_level());
}

void LightLevelServer::handle_light_level_history()
{
  String output = "time,light level\n";
  unsigned entries_retrieved;
  while(_light_log.get_light_level_history(_light_level_buffer, LIGHT_LEVEL_HISTORY_ENTRIES, entries_retrieved) && entries_retrieved > 0)
  {
    for(unsigned i = 0; i < entries_retrieved; i++)
    {
      output += String("") + _light_level_buffer[i].time + "," + _light_level_buffer[i].light_level + "\n";
    }
  }

  send(200, "text/plain", output);
}

