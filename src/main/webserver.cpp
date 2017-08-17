#include "webserver.h"

WiFiServer wifiServer(80);

Webserver::Webserver()
:
	webserverPca9633()
{
	StartServer();
	Serial.println("webserver constructor was called");
}

Webserver::~Webserver()
{
}

void Webserver::StartServer()
{
	wifiServer.begin();
	Serial.println("Server is running");
	MDNS.addService("http", "tcp", 80);
	if(WiFi.localIP() == ZeroIp)
	{
		Serial.println("\nconnect to your Esp as an AP");
		Serial.print("Connect to: http://");
		Serial.print(WiFi.softAPIP());
		Serial.println("/");
	}
	else
	{
		Serial.println("\nconnect to your own WiFi network");
		Serial.print("Connect to: http://");
		Serial.print(WiFi.localIP());
		Serial.println("/");
	}
}

void Webserver::OpenHtmlFile()
{
	if(SPIFFS.exists(htmlWebsite))
	{
		File f = SPIFFS.open(htmlWebsite, "r");
		if(!f)
		{
			Serial.println("can not read the file");
			Serial.println("");
		}
		else
		{
			String s;
			while(f.available())
			{
				s += f.readStringUntil('\n');
				
			}
			client.println(s);
		}
		f.close();
	}
}

void Webserver::WebSite()
{
	int clientTimeOutCounter = 0;
	OpenHtmlFile();
	client = wifiServer.available();
	if(!client)
		return;
	
	Serial.println("\nnew client");
	while(!client.available())
	{
		delay(1);
		clientTimeOutCounter++;

		if(clientTimeOutCounter >= 250)
		{
			Serial.println("Connection timeout");
			return;
		}
	}
	
	request = client.readStringUntil('\r');
	client.flush();
	
	if(request == "")
	{
		client.stop();
		return;
	}
	
	GetPathAndParameterString();
	
	if((path == DefaultWebsite) || (path == "/"))
		htmlWebsite = DefaultWebsite;
	else if(path == ConfigWebsite)
		htmlWebsite = ConfigWebsite;
	else if(path == GetIpAddressWebsite)
		client.print(PrintIpAddressToClient());
	
	while(parameterString.length() > 0)
	{
		ReadValuesFromParameterString();
		
		if(parameterString.length() >= 0)
		{
			if(color.startsWith("r"))
			{
				if(colorValue.toInt() > 255 || colorValue.toInt() < 0)
				{
					htmlWebsite = ColorOutOfRangeWebsite;
					Serial.println("red value is out of range");
					return;
				}
				pwmRedValue = (uint8_t)colorValue.toInt();
				webserverPca9633.WriteToPwm2(pwmRedValue);
				htmlWebsite = DefaultWebsite;
			}
			else if(color.startsWith("g"))
			{
				if(colorValue.toInt() > 255 || colorValue.toInt() < 0)
				{
					htmlWebsite = ColorOutOfRangeWebsite;
					Serial.println("green value is out of range");
					return;
				}
				pwmGreenValue = (uint8_t)colorValue.toInt();
				webserverPca9633.WriteToPwm3(pwmGreenValue);
				htmlWebsite = DefaultWebsite;
			}
			else if(color.startsWith("b"))
			{
				if(colorValue.toInt() > 255 || colorValue.toInt() < 0)
				{
					htmlWebsite = ColorOutOfRangeWebsite;
					Serial.println("blue value is out of range");
					return;
				}
				pwmBlueValue = (uint8_t)colorValue.toInt();
				webserverPca9633.WriteToPwm1(pwmBlueValue);
				htmlWebsite = DefaultWebsite;
			}
			
			if(color.startsWith("ssid"))
			{
				newSsid = ConvertUrlToString(colorValue);
				newSsidWasSet = true;
			}				
			else if(color.startsWith("password"))
				newPassword = ConvertUrlToString(colorValue);
		}
	}
	
	if(newSsidWasSet)
	{
		newSsidWasSet = false;
		SaveConfig();
		htmlWebsite = DefaultWebsite;
		OpenHtmlFile();
		if(!client.available())
			client.stop();
		delay(1000);
		ESP.restart();
	}
}

void Webserver::GetPathAndParameterString()
{
	startIndex = request.indexOf(GetStart);
	
	if(startIndex < 0)
	{
		Serial.println("no parameters are set");
		return;
	}
	
	startIndex +=+ GetStart.length();
	endSpaceIndex = request.indexOf(" ", startIndex);
	endQuestionmarkIndex = request.indexOf("?", startIndex);
	
	if(endSpaceIndex > 0)
	{
		if(endQuestionmarkIndex > 0)
		{
			path = request.substring(startIndex, endQuestionmarkIndex);
			parameterString = request.substring(endQuestionmarkIndex + 1, endSpaceIndex);
		}
		else
		{
			path = request.substring(startIndex, endSpaceIndex);
		}
	}
}

void Webserver::ReadValuesFromParameterString()
{
	int equalSignIndex = parameterString.indexOf("=");
	int ampersandIndex = parameterString.indexOf("&");
	
	if(equalSignIndex > 0)
	{
		color = parameterString.substring(0, equalSignIndex);
		if(ampersandIndex >= equalSignIndex)
		{
			colorValue = parameterString.substring(equalSignIndex + 1, ampersandIndex);
			parameterString = parameterString.substring(ampersandIndex + 1, parameterString.length());
		}
		else
		{
			colorValue = parameterString.substring(equalSignIndex + 1, parameterString.length());
			parameterString = "";
		}
	}
	else
	{
		color = "";
		colorValue = "";
	}
}

String Webserver::ConvertUrlToString(String url)
{
	String convertedString;
	int i;
	for(i = 0; i < url.length(); i++)
	{
		if(url[i] == '%')
		{
			String hex = url.substring(i + 1, i + 3);
			int number = HexCharToInt(hex[0]) * 16 + HexCharToInt(hex[1]);
			convertedString += (char)number;
			i += 2;
		}
		else if(url[i] == '+')
			convertedString += ' ';
		else
			convertedString += url[i];
	}
	return convertedString;
}

int Webserver::HexCharToInt(char c)
{
  const char *hex = "0123456789ABCDEF";
  for (int i = 0; i < 16; i++)
  {
	if (hex[i] == c)
	  return i;
  }
  return -1;
}

bool Webserver::SaveConfig() 
{
	Serial.println("Saving...");
	
	StaticJsonBuffer<400> jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();
	json["ssid"] = newSsid;
	json["password"] = newPassword;
	
	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile)
	{
		Serial.println("Failed to open config file for writing");
		return false;
	}
	
	json.printTo(configFile);
	delay(1000);
	configFile.close();
	return true;
}

String Webserver::PrintIpAddressToClient()
{
	String s;
	s += "<html>";
	s += "<head> <meta charset=\"utf-8\">";
	s += "<title>get ip-address</title>";
	s += "</head>";
	s += "<body>";
	s += "<meta name=\"viewport\"content=\"width=device-width, initial-scale=1.0\" />";
	s += "<center>";
	s += "<br>";
	s += "connect your smartphone or tablet to: http://";
	if(WiFi.localIP() == ZeroIp)
		s += WiFi.softAPIP().toString();
	else
		s += WiFi.localIP().toString();
	s += "</center>";
	s += "</body>";
	s += "</html>";
	
	return s;
}