#include <Arduino.h>
#include "SDLog.h"
#include "SD.h"
#include "SPI.h"

bool HEADER_ADDED = false;

/**
 * Opens a file "DATALOG.csv" and logs passed sensor data.
*/		
SDLog::SDLog(float temperature, float humidity,
	uint8_t day, uint8_t month, uint16_t year,
	uint8_t hour, uint8_t minute, uint8_t second,
	double longitude, double latitude) {
	
	/* open/make a file */
	File data = SD.open("datalog.csv", FILE_WRITE);
	if(data) {	
		/* Push data to CSV file */
		addHeader(data);
		
		data.print(temperature );
		data.print(F(" F,"));
		data.print(humidity);
		data.print(" %,");
		
		data.print(day);
		data.print(F("/"));
		data.print(month);
		data.print(F("/"));
		data.print(year);
		data.print(F(","));
		
		data.print(hour);
		data.print(F(":"));
		data.print(minute);
		data.print(F(":"));
		data.print(second);
		data.print(F(","));
		
		data.print(longitude);
		data.print(F("°,"));
		data.print(latitude);
		data.println(F("°,"));
		
		data.close();

	} else {
		return;
	}
}

/**
 * Add a header to the file on the first line
*/
void SDLog::addHeader(File data) {	
	
	if(!HEADER_ADDED) {
		data.println(F("Temperature, Humidity, Date, Time, Longitude, Latitude"));
		HEADER_ADDED = true;
	}
}

