#include "Humidity.h"
#include "Arduino.h"

float Humidity::read(int pin) {
	int analog = analogRead(pin);
	// convert analog input to digital voltage readout
	float digital = analog * (5.0 / 1023);
	// convert voltage readout to humidity percentage
	float humidity = -12.5 + (125 * (digital / 3.3));
	return humidity;
}
