#include "pca9633.h"

Pca9633::Pca9633()
:
	i2c()
{
	i2c.WriteToRegister(SlaveAddress, RegisterAddressMode1, DefaultValueMode1);
	i2c.WriteToRegister(SlaveAddress, RegisterAddressMode2, DefaultValueMode2);
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm0, DefaultValuePwm0);
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm1, DefaultValuePwm1);
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm2, DefaultValuePwm2);
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm3, DefaultValuePwm3);
	i2c.WriteToRegister(SlaveAddress, RegisterAddressLedOut, DefaultValueLedOut);
	Serial.println("pca constructor was called");
}

Pca9633::~Pca9633()
{
}

void Pca9633::WriteToPwm0(uint8_t value)
{
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm0, value);
}

void Pca9633::WriteToPwm1(uint8_t value)
{
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm1, value);
}

void Pca9633::WriteToPwm2(uint8_t value)
{
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm2, value);
}

void Pca9633::WriteToPwm3(uint8_t value)
{
	i2c.WriteToRegister(SlaveAddress, RegisterAddressPwm3, value);
}

void Pca9633::WriteToLedOut(uint8_t value)
{
	i2c.WriteToRegister(SlaveAddress, RegisterAddressLedOut, value);
}