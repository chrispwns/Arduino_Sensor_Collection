/*
Name:		SDLogger.h
Purpose:	Allows data logging to a file on an inserted SD Card
Created:	2/23/2017
Author:	Christopher Naron
*/

#include "Arduino.h";
#include <SPI.h>
#include <SD.h>
#include "SDLogger.h";

//		PUBLIC


/*
* Constructs an SDLogger object that creates an output file for tracking data.
*
 * @param temperature	value to be input in the temperature field of the file.
 * @param humidity	value to be input in the humidity field of the file.
 * @param time	value to be input in the time field of the file.
 * @param location	value to be input in the location field of the file.
*/
SDLogger::SDLogger(float temperature, float humidity, String currentTime, String location)
{

	String data = String(temperature) + "," + String(humidity) + "," + currentTime + "," + location;	// format the data for output

	if (SD.exists("datalog.csv")) {		// write sensor readings if a datalog is there.
		writeFile(data);
	}
	else	// create a new datalog if there's not one already.
	{
		Serial.println("Creating datalog.csv");
		createFile();
	}


}

/*
 * dumpFile() 
 * pushes all collected sensor readings to the Serial Monitor
 * called when "l" is sent as a serial message to the program.
*/
void SDLogger::dumpFile() {

	File datalog = SD.open("datalog.csv", FILE_READ);
	Serial.print("\ndatalog.csv: \n\n");

	if (datalog)	// if the file is available, read the file
	{
		while (datalog.available()) {	// read from the file until there's nothing else in it:
			Serial.write(datalog.read());
		}

		datalog.close();
		Serial.println("\n");
	}

	else	// if the file cannot be opened give error report
	{
		Serial.println("\n\nLine 63: failed to open file for reading.\n\n");
	}
}

/*
 * deleteFile()
 * removes the datalog file from the SD Card.
 * called when "r" is sent as a serial message to the program.
*/
void SDLogger::deleteFile()
{
	SD.remove("datalog.csv");
	Serial.println("datalog.csv deleted.\nCreating new datalog.csv");
	createFile();
}

//		PRIVATE

/*
 * createFile()
 * creates a new datalog file.
*/
void SDLogger::createFile()
{
	File datalog = SD.open("datalog.csv", FILE_WRITE);

	if (datalog) {		// datalog exists and is available push sensor data to it.
		datalog.println("Temperature F,Humidity %, Time GMT, Location");
		datalog.close();
	}
}

/*
 * writeFile()
 * pushes sensor data to the datalog file.
 * @param a formatted row of sensor data.
*/
void SDLogger::writeFile(String data)
{
	File datalog = SD.open("datalog.csv", FILE_WRITE);

	if (datalog) {		// datalog exists and is available push sensor data to it.
		datalog.println(data);
		datalog.close();
	}
	else
	{
		Serial.println("\n\nLine 105: Failed to open file for writing.\n\n");
	}
}