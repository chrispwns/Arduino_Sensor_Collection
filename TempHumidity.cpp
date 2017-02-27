/*
TempHumidity.h - Library for collecting Temperature and Humidity from the SHT30A - EASY.
Author: Christopher Naron 2 / 26 / 2017
Licensing : Unknown ATM.
*/
#include "Arduino.h";
#include "TempHumidity.h";

/**
* Initialize temperature and humidity collection.
* @param temperaturePin   pin location
* @param humidityPinpin   location.
* @param isCelsius  true for celsius conversion.
**/
TempHumidity::TempHumidity(uint8_t temperaturePin, uint8_t humidityPin, bool isCelsius) {

	this->isCelsius = isCelsius;

	// initialize the temperature and humidity sensors
	int tempSerialIn = analogRead(temperaturePin);
	int humidSerialIn = analogRead(humidityPin);

	const float VDD = 3.3;	// 3.3v input from board

	// convert analog sensor input to digital values.
	float tempVoltage = analogToDigital(tempSerialIn);
	float humidityVoltage = analogToDigital(humidSerialIn);

	// Spec sheet voltage -> temperature/humidity conversions.
	// http://www.mouser.com/ds/2/682/Sensirion_Humidity_SHT3x_Datasheet_analog-767292.pdf
	temperature = -88.375 + (393.75 * (tempVoltage / VDD));  // fahrenheit by default
	humidity = -12.5 + (125 * (humidityVoltage / VDD));

	dataOutput(temperature, humidity, isCelsius); // print to serial monitor
}

/**
* Returns a float containing the Temperature data.
*/
float TempHumidity::getTemperature() {
	return temperature;
}


/**
* Returns a float containing the Humidity data.
*/
float TempHumidity::getHumidity() {
	return humidity;
}


//    PRIVATE


// If set true will output celsius, otherwise fahrenheit.
volatile bool isCelsius;
// Store sensor data for output.
static float humidity;
static float temperature;

/**
* Store sensor data for returning with get and output for debugging.
* @param temperature
* @param humidity
* @param isCelsius
*/
void TempHumidity::dataOutput(float temperature, float humidity, bool isCelsius)
{
	// Initialize strings/chars for output.
	const char PCNT = 37;	// percent ascii code. Used in output formatting.
	const String TEMP_STR = "Temperature: ";
	const String HUMID_STR = "\tHumidity: ";
	const String FAHRENHEIGHT = " F";
	const String CELSIUS = " C";

	if (isCelsius == true)
	{
		temperature = (temperature - 32) * 5 / 9;	// convert to celsius.
		Serial.println(TEMP_STR + temperature + CELSIUS + HUMID_STR + humidity +
			PCNT);
	}
	else	// output fahrenheit
	{ 
		Serial.println(TEMP_STR + temperature + FAHRENHEIGHT + HUMID_STR +
			humidity + PCNT);
	}
}

/**
* Converts a 10-bit analog inut to digital voltage output.
* @param sensorValue
*/
float TempHumidity::analogToDigital(int sensorValue)
{
	const float BASE_VOLTAGE = 5.0;
	const int ANALOG_RANGE = 1023; // 10-bit resolution.
	return sensorValue * (BASE_VOLTAGE / ANALOG_RANGE);  // standard ADC formula.
}

/*
* Allows changes between fahrenheit and celsius discretely
* send "c" over serial for celsius and "f" for fahrenheit
*/
void TempHumidity::serialEvent()
{
	while ( Serial.available() )
	{
		char keybIn = (char)Serial.read();		// read character sent from serial input

		switch (keybIn) {		// change format to f or c discretely.
		case 'f':
			isCelsius = false;
			break;
		case 'c':
			isCelsius = true;
			break;
		}
	}
}