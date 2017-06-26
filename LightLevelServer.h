#ifndef __LIGHT_LEVEL_SERVER_H__
#define __LIGHT_LEVEL_SERVER_H__

#include "OOWebServer.h"

#include "LightLevelLog.h"


#define LIGHT_LEVEL_HISTORY_BUFFER_SIZE (16*1024)
#define LIGHT_LEVEL_HISTORY_ENTRIES     (LIGHT_LEVEL_HISTORY_BUFFER_SIZE / sizeof(LightLevelLog::LightLevel))

class LightLevelSensor;


class LightLevelServer : public OOWebServer<LightLevelServer>
{
  public:
    LightLevelServer(int server_port, LightLevelSensor & light_level_sensor, LightLevelLog & light_log, const String &templates_base_dir);

    void on_setup();
    void on_loop();
    
  private:
    void server_begin();
    
    void handle_root();
    void handle_light_level();
    void handle_light_level_history();
  
    const LightLevelSensor & _light_level_sensor;
    const LightLevelLog & _light_log;

    LightLevelLog::LightLevel _light_level_buffer[LIGHT_LEVEL_HISTORY_ENTRIES];
};


#endif // __LIGHT_LEVEL_SERVER_H__