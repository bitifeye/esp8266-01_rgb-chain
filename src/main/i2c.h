#ifndef I2C_H_
#define I2C_H_

#include <Arduino.h>
#include <Wire.h>

using namespace std;

class I2c
{
	public:
		// methods
		I2c();
		virtual ~I2c();
		
		void WriteToRegister(uint8_t i2cSlaveAddress, uint8_t slaveRegisterAddress, uint8_t commandByte);
		uint8_t ReadFromRegister(uint8_t i2cSlaveAddress, uint8_t slaveRegisterAddress);
		
	private:
		// constants
		const int SDA = 0;				// GPIO0
		const int SCL = 2;				// GPIO2
		const int NumberOfBytes = 1;	// one bytes to recive from the slave register
};

#endif //I2C_H_