#pragma once


#include <stdint.h>
#include <WString.h>
#include <ESP8266WiFi.h>


enum HTTPMethod
{

};

class HTTPUpload
{

};

class RequestHandler
{

};

class ESP8266WebServer
{
public:
    ESP8266WebServer(const IPAddress ip_address, int port);
    ESP8266WebServer(int port);
    void handleClient();
    void send(uint16_t code, const String & encoding, const String & message);

};