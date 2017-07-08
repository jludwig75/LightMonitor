#include "LightLevelApp.h"


#define LIGHT_SENSOR_PIN                A0
#define WEB_SERVER_PORT                 80
#define LIGHT_LEVEL_UPDATE_INTERVAL_MS  (5 * 60 * 1000)   // 5 Minutes
#define TIME_MANAGER_UPDATE_INTERVAL_MS (60 * 60 * 1000)  // 1 hour
#define WIFI_SSID                       "My SSID"
#define WIFI_PASSWORD                   "XXXXXXXXXXXXX"
#define LIGHT_LEVEL_LOG_FILE_NAME       "LIGHTLVL.LOG"


LightLevelApp app(LIGHT_SENSOR_PIN,
                  LIGHT_LEVEL_LOG_FILE_NAME,
                  LIGHT_LEVEL_UPDATE_INTERVAL_MS,
                  TIME_MANAGER_UPDATE_INTERVAL_MS,
                  WEB_SERVER_PORT,
                  WIFI_SSID, WIFI_PASSWORD);


void setup()
{
  app.on_setup();
}

void loop()
{
  app.on_loop();
}
