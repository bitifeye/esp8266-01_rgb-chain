#ifndef ESP01_H_
#define ESP01_H_

#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>

#include <string.h>
#include "FS.h"

#include "pca9633.h"
#include "webserver.h"

class Esp01
{
	public:
		// methods
		Esp01();
		virtual ~Esp01();
		
		void StartWifiConnection();
		void StartAccessPoint();
		void StartSpiffs();
		bool LoadConfig() ;
		
	private:
		// hostname
		const char* HostName = "esp8266";
		
		// constants for wifi connection
		String ssid;
		String password;
		
		// constants for Access Point
		const char* ApSsid = "ESP-01";						// set the AP-Ssid
		const char* ApPassword;								// set the Ap-Password
		
		// variables for the memory
		bool spiffsActive = false;
		bool configAreLoaded = false;
};

#endif //ESP01_H_