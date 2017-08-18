#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>

#include <string.h>
#include "FS.h"

#include "esp01.h"
#include "pca9633.h"

class Webserver
{
	public:
		// variables
		uint8_t pwmRedValue;
		uint8_t pwmBlueValue;
		uint8_t pwmGreenValue;
		
		int startIndex, endSpaceIndex, endQuestionmarkIndex;
		
		bool newSsidWasSet = false;
		
		String request;
		String path;
		String parameterString;
		String color;
		String colorValue;
		String newSsid;
		String newPassword;
		
		// methods
		Webserver();
		virtual ~Webserver();
		
		void WebSite();
		void GetPathAndParameterString();
		void OpenHtmlFile();
		void ReadValuesFromParameterString();
		void StartServer();
		String ConvertUrlToString(String url);
		int HexCharToInt(char c);
		bool SaveConfig();
		String PrintIpAddressToClient();
		
	private:
		// instance
		Pca9633 webserverPca9633;
		WiFiClient client;
		
		// website names
		String const DefaultWebsite = "/color_options.html";
		String const ColorOutOfRangeWebsite = "/color_out_of_range.html";
		String const ConfigWebsite= "/config.html";
		String const GetIpAddressWebsite = "/get_ip_address.html";
		String const GetStart = "GET ";
		
		String htmlWebsite = "/color_options.html";
		
		// unacceptable IP address
		IPAddress const ZeroIp = (0, 0, 0, 0);
};
#endif // WEBSERVER_H_
