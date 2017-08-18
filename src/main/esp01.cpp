#include "esp01.h"

Esp01::Esp01()
{
	Serial.begin(9600, SERIAL_8N1, SERIAL_TX_ONLY);
	pinMode(2, OUTPUT);
	pinMode(0, OUTPUT);
	SPIFFS.begin();
	StartSpiffs();
	
	configAreLoaded = LoadConfig();
	
	StartWifiConnection();
	
	Serial.println("esp01 constructor was called");
}

Esp01::~Esp01()
{
}

void Esp01::StartWifiConnection()
{
	int counter = 0;
	WiFi.disconnect();
	if(!configAreLoaded)
	{
		StartAccessPoint();
		return;
	}
	Serial.print("\n\nTrying to connect to: ");
	Serial.println(ssid);
	WiFi.mode(WIFI_STA);
	WiFi.hostname(HostName);
	WiFi.begin(ssid.c_str(), password.c_str());
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
		counter++;
		if((WiFi.status() != WL_CONNECTED) && (counter > 30))
		{
			Serial.println("\n\nWiFi connection failed\n\n");
			StartAccessPoint();
			return;
		}
	}
	
	Serial.println("");
	Serial.println("You are connected");
	Serial.println("");
	
	if(!MDNS.begin(HostName))
	{
		Serial.println("Error setting up MDNS responder!");
	}
}

void Esp01::StartAccessPoint()
{
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ApSsid, ApPassword);
	Serial.println("access point is running");
	MDNS.begin(HostName);
}

void Esp01::StartSpiffs()
{
	uint32_t realSize = ESP.getFlashChipRealSize();
    uint32_t ideSize = ESP.getFlashChipSize();
    FlashMode_t ideMode = ESP.getFlashChipMode();
	
	if(ideSize != realSize)
		Serial.println("Flash Chip configuration wrong!\n");
    else 
		Serial.println("Flash Chip configuration ok.\n");
	
	if(SPIFFS.begin())
	{
		Serial.println("SPIFFS Active");
		Serial.println();
		spiffsActive = true;
	}
	else
	{
		Serial.println("Unable to activate SPIFFS");
		uint32_t realSize = ESP.getFlashChipRealSize();
		uint32_t ideSize = ESP.getFlashChipSize();
		FlashMode_t ideMode = ESP.getFlashChipMode();

		Serial.println("");
		Serial.printf("Flash real id:   %08X\n", ESP.getFlashChipId());
		Serial.printf("Flash real size: %u\n\n", realSize);

		Serial.printf("Flash ide  size: %u\n", ideSize);
		Serial.printf("Flash ide speed: %u\n", ESP.getFlashChipSpeed());
		Serial.printf("Flash ide mode:  %s\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
	}
	delay(2000);
}

bool Esp01::LoadConfig() 
{
	if(SPIFFS.exists("/config.json"))
	{
		File configFile = SPIFFS.open("/config.json", "r");
		if(!configFile) 
		{
			Serial.println("Failed to open config file");
			return false;
		}
		
		size_t size = configFile.size();
		if(size > 1024) 
		{
			Serial.println("Config file size is too large");
			return false;
		}
		
		std::unique_ptr<char[]> buf(new char[size]);
		configFile.readBytes(buf.get(), size);
		
		StaticJsonBuffer<400> jsonBuffer;
		JsonObject& json = jsonBuffer.parseObject(buf.get());
		
		if(!json.success()) 
		{
			Serial.println("Failed to parse config file");
			return false;
		}
		
		ssid = json["ssid"].asString();
		password = json["password"].asString();
		return true;
	}
	else
		return false;
}
	
	