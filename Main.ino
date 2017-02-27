/*
Name:    Arduino.ino
Created: 2/23/2017 3:34:29 PM
Author:  Christopher Naron
*/
#include "Arduino.h";
#include "TempHumidity.h";
#include "SPI.h";
#include "SD.h";
#include "SDLogger.h";

/*
 * dumplog: allows for datalog dumping to serial monitor after execution.
 * removeFile: allows for datalog deletion after execution.
*/
volatile bool dumpLog = false;
volatile bool removeFile = false;

void setup() {

	const int BAUD_RATE = 9600; // Initialize serial input with BAUD of 9600
	Serial.begin(BAUD_RATE);

	if (!SD.begin()) { // make sure SD card was initialized.
		Serial.println("SD Initialization Failure.");
		return;
	}
	Serial.println("SD Initialization Success.");
}

void loop() {

	// collect sensor data
	TempHumidity tempHumSensor = TempHumidity::TempHumidity(A0, A1, false);
	
	// save sensor data
	float temperature = tempHumSensor.getTemperature();
	float humidity = tempHumSensor.getHumidity();
	
	// pass sensor data to be saved on the SD card.
	SDLogger SDLog = SDLogger::SDLogger(temperature, humidity, "now", "home");

	// print the saved data to the serial monitor when dumpLog is true, then reset it false. 
	if (dumpLog == true) {
		SDLog.dumpFile();
		dumpLog = false;
	}
	// delete the current datalog file when deleteFile is true, then reset it false.
	if (removeFile == true) {
		SDLog.deleteFile();
		removeFile = false;
	}

	delay(5000);
}

void serialEvent() {

	while (Serial.available()) {
		char keybIn = (char)Serial.read(); // capture serial input

		switch (keybIn) {

		case 'l': // print file contents
			dumpLog = true;
			break;

		case 'r': // delete file
			removeFile = true;
			break;
		}
	}
}
