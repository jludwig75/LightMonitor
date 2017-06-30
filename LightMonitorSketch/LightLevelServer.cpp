#define _CRT_SECURE_NO_WARNINGS

#include "LightLevelServer.h"

#include "LightLevelSensor.h"
#include "TimeManager.h"
#include "tracing.h"
#include <Timezone.h>
#include <TimeLib.h>


LightLevelServer::LightLevelServer(int server_port, LightLevelSensor & light_level_sensor, LightLevelLog & light_log, const TimeManager & time_manager, const String & templates_base_dir) :
 OOWebServer<LightLevelServer>(templates_base_dir, server_port),
 _light_level_sensor(light_level_sensor),
 _light_log(light_log),
  _tz(NULL),
  _time_manager(time_manager)
{
}

LightLevelServer::~LightLevelServer()
{
    delete _tz;
}

void LightLevelServer::on_setup()
{
    TimeChangeRule myDST = { "", Second, Sun, Mar, 2, -360 };    //Daylight time = UTC - 6 hours
    TimeChangeRule mySTD = { "", First, Sun, Nov, 2, -420 };     //Standard time = UTC - 7 hours
    strncpy(myDST.abbrev, "?DT", sizeof(myDST.abbrev));
    strncpy(mySTD.abbrev, "?ST", sizeof(mySTD.abbrev));
    _tz = new Timezone(myDST, mySTD);
    begin();
}

static String pad_string(const String & _str, size_t width, char fill_char)
{
    String str = _str;
    if (str.length() < width)
    {
        size_t fill_amount = width - str.length();
        for (size_t i = 0; i < fill_amount; i++)
        {
            str = fill_char + str;
        }
    }

    return str;
}


String LightLevelServer::to_local_time_string(time_t utc_time) const
{
    time_t local_time = _tz->toLocal(utc_time);
    tmElements_t tm;
    breakTime(local_time, tm);

    String time_string = String((int)tm.Month) + "/" + String((int)tm.Day) + "/" + String(tmYearToCalendar(tm.Year)) + " " +
        String((int)tm.Hour) + ":" + pad_string(String((int)tm.Minute), 2, '0') + ":" + pad_string(String((int)tm.Second), 2, '0');

    return time_string;
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
  inf_printf("Web server handled path \"/\":\n%s\n", output.c_str());
}

void LightLevelServer::handle_light_level() {
    time_t t = _time_manager.get_time();
    String t_s = to_local_time_string(t);
  inf_printf("Web server handling path \"/light_level\"\n");
  String output = String("Light level = ") + String(_light_level_sensor.get_current_light_level()) + "<br/>";
  output += String("Time =") + t_s;
  send(200, "text/plain", output);
  inf_printf("Web server handled path \"/light_level\":\n%s\n", output.c_str());
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
      output += String("") + to_local_time_string(_light_level_buffer[i].time) + "," + String(_light_level_buffer[i].light_level) + "\n";
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
    inf_printf("Web server handled path \"/light_history\":\n%s\n", output.c_str());
  }
}

