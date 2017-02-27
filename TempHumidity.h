/*
TempHumidity.h - Library for collecting Temperature and Humidity from the SHT30A-EASY.
Author: Christopher Naron 2/26/2017
Licensing: Unknown ATM.
*/
#ifndef TempHumidity_h
#define TempHumidity_h

#include "Arduino.h"

class TempHumidity {
public:
	TempHumidity(uint8_t temperaturePin, uint8_t humidityPin, bool isCelsius);
	float getTemperature();
	float getHumidity();


private:
	float analogToDigital(int sensorValue);
	void dataOutput(float temperature, float humidity, bool celsius);
	void serialEvent();
	float temperature;
	float humidity;
	volatile bool isCelsius;



};

#endif // !TempHumidity_h
