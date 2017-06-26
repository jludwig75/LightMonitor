#include "wifi_manager.h"

#include "tracing.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


void connect_wifi(String ssid, String password)
{
  // Connect to WiFi network
  WiFi.begin(ssid.c_str(), password.c_str());
  inf_printf("\n\r \n\rWorking to connect to SSID \"%s\"", ssid.c_str());

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    inf_printf(".");
  }
  
  inf_printf("\nConnected to %s\n", ssid.c_str());
  inf_printf("IP address: %s\n", WiFi.localIP().toString().c_str());
}

