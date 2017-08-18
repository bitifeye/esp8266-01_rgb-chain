#ifndef PCA9633_H_
#define PCA9633_H_

#include <Arduino.h>
#include "i2c.h"

class Pca9633
{
	public:
		// variable for possible read command
		uint8_t activByte;
		
		// methods
		Pca9633();
		virtual ~Pca9633();
		
		void WriteToPwm0(uint8_t value);			// value range 0..255
		void WriteToPwm2(uint8_t value);			// value range 0..255
		void WriteToPwm1(uint8_t value);			// value range 0..255
		void WriteToPwm3(uint8_t value);			// value range 0..255
		void WriteToLedOut(uint8_t value);			// value range 0..255
		
	private:
		// instance
		I2c i2c;
		
		// device address
		static const uint8_t SlaveAddress = 0x62;
		
		// register address
		static const uint8_t RegisterAddressMode1 = 0x00;
		static const uint8_t RegisterAddressMode2 = 0x01;		
		static const uint8_t RegisterAddressPwm0 = 0x02;		// not used
		static const uint8_t RegisterAddressPwm1 = 0x03;		// blue
		static const uint8_t RegisterAddressPwm2 = 0x04;		// red
		static const uint8_t RegisterAddressPwm3 = 0x05;		// green
		static const uint8_t RegisterAddressLedOut = 0x08;
		
		// register default values
		static const uint8_t DefaultValueMode1 = 0x80;
		static const uint8_t DefaultValueMode2 = 0x15;			// the 4 LED outputs are conﬁgured with a totem pole output
		static const uint8_t DefaultValuePwm0 = 0x00;			// off
		static const uint8_t DefaultValuePwm1 = 0x00;			// off
		static const uint8_t DefaultValuePwm2 = 0x00;			// off
		static const uint8_t DefaultValuePwm3 = 0x00;			// off
		static const uint8_t DefaultValueLedOut = 0xAA;			// LEDx on it's own brightness control
};

#endif //PCA9633_H_