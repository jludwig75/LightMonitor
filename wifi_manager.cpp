#include "wifi_manager.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>


void connect_wifi(String ssid, String password)
{
  // Connect to WiFi network
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

