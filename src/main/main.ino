#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>

#include <string.h>
#include "FS.h"

#include <Wire.h>

#include "pca9633.h"
#include "webserver.h"
#include "esp01.h"
#include "i2c.h"

Webserver mainWebserver;

void setup() 
{
	// put your setup code here, to run once:
	Esp01 mainEsp01;
	Webserver mainWebserver;
}

void loop() 
{
	// put your main code here, to run repeatedly:
	mainWebserver.WebSite();
}