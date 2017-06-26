#include "../LightMonitorSketch/LightLevelServer.h"


LightLevelServer::LightLevelServer(int server_port, LightLevelSensor & light_level_sensor, LightLevelLog & light_log, const String &templates_base_dir) :
    OOWebServer<LightLevelServer>(templates_base_dir, server_port),
    _light_level_sensor(light_level_sensor),
    _light_log(light_log)
{

}

void LightLevelServer::on_setup()
{

}

void LightLevelServer::on_loop()
{

}

void LightLevelServer::server_begin()
{

}
