#include "Temperature.h"
#include "Arduino.h"

/**
 * Reads a temperature from the specified analog pin
 * only works with SHT30A-EZ
*/ 
float Temperature::read(int pin) {
	int analog = analogRead(pin);
	//Convert analog intput to a digital voltage value 
	float digital = analog * (5.0 / 1023);
	// voltage readout is converted into fahrenheit
	float temperature = -88.375 + (393.75 * (digital / 3.3));
	return temperature;
}
