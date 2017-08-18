#include "i2c.h"

I2c::I2c()
{
	Wire.pins(SDA, SCL);
	Wire.begin(SDA, SCL);
	Serial.println("i2c constructor was called");
}

I2c::~I2c()
{
}

void I2c::WriteToRegister(uint8_t i2cSlaveAddress, uint8_t slaveRegisterAddress, uint8_t commandByte)
{
	if(commandByte > 255 || commandByte < 0)
	{
		Serial.println("commandByte value out of range");
		return;
	}
	
	Wire.beginTransmission(i2cSlaveAddress);
    Wire.write(slaveRegisterAddress);
    Wire.write(commandByte);
	Wire.endTransmission();
}

uint8_t I2c::ReadFromRegister(uint8_t i2cSlaveAddress, uint8_t slaveRegisterAddress)
{
	uint8_t receivedData;
	
	Wire.beginTransmission(i2cSlaveAddress);
    Wire.write(slaveRegisterAddress);
    Wire.endTransmission();
    Wire.beginTransmission(i2cSlaveAddress);
    Wire.requestFrom(slaveRegisterAddress, NumberOfBytes);
    
	while (Wire.available())
		receivedData = Wire.read();
	
    Wire.endTransmission();
	
	return receivedData;
}