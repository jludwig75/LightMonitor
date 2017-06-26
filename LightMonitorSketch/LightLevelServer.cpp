#include "LightLevelServer.h"

#include "LightLevelSensor.h"
#include "tracing.h"


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
  inf_printf("Starting Light Monitor Web Server...\n");
  on("/", &LightLevelServer::handle_root);
  on("/light_level", &LightLevelServer::handle_light_level);
  on("/light_history", &LightLevelServer::handle_light_level_history);
  inf_printf("Light Monitor Web Server started\n");
}

void LightLevelServer::handle_root() {
  inf_printf("Web server handling path \"/\"\n");
  String output = "Hello from the esp8266 web server.";
  send(200, "text/plain", output);
  inf_printf("Web server handled path \"/\":\n%s", output.c_str());
}

void LightLevelServer::handle_light_level() {
  inf_printf("Web server handling path \"/light_level\"\n");
  String output = String("Light level = ") + String(_light_level_sensor.get_current_light_level());
  send(200, "text/plain", output);
  inf_printf("Web server handled path \"/light_level\":\n%s", output.c_str());
}

void LightLevelServer::handle_light_level_history()
{
  inf_printf("Web server handling path \"/light_history\"\n");
  String output = "time,light level\n";
  unsigned entries_retrieved;
  unsigned start_entry = 0;
  bool ret = true;
  while((ret = _light_log.get_light_level_history(_light_level_buffer, LIGHT_LEVEL_HISTORY_ENTRIES, start_entry, entries_retrieved)) && entries_retrieved > 0)
  {
    for(unsigned i = 0; i < entries_retrieved; i++)
    {
      output += String("") + String(_light_level_buffer[i].time) + "," + String(_light_level_buffer[i].light_level) + "\n";
    }

    start_entry += entries_retrieved;
  }

  if (!ret)
  {
    String output = "Web server encountered an error reading from the log file while handling path \"/light_history\".";
    err_printf("%s\n", output.c_str());
    send(500, "text/plain", output);
  }
  else
  {
    send(200, "text/plain", output);
    inf_printf("Web server handled path \"/light_history\":\n%s", output.c_str());
  }
}

