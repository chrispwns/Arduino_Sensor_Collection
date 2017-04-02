#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "Temperature.h"
#include "Humidity.h"
#include "SDLog.h"

TinyGPSPlus gps;
SoftwareSerial gpsSerial(8, 7);

const int CHIP_SELECT 		= 10;   // SD card select pin
const int UPDATE_INTERVAL 	= 5000; // update interval for sd card

void setup() { 	
	Serial.begin(115200);
	gpsSerial.begin(9600);
    SD.begin(10); 
    
    // uncomment to remove old csv file on startup
    //SD.remove("DATALOG.csv");
    
}

/*
 * loop()
 * 
 * The loop will update each 10ms so that it's fast enough to capture
 *  gps data without overflowing; however, since data doesn't need to be
 *  logged at that rate when the timer hits a set threshold it will
 *  log the data
 */
void loop() {

	
	/* pass gps data to TinyGPS++ */
	while (gpsSerial.available() > 0) {
		gps.encode(gpsSerial.read());
	}
	
	/* Update the sd card at the update interval defined above
	 *  give it a 20ms tolerance since millis() isn't a perfect clock. 
	 * also added a check to  make sure initial fix is captured before
	 *  pushing data to SD*/
	if( (millis() % UPDATE_INTERVAL < 20) && ( millis() > 5000 )) {
		SDLog( Temperature().read(0), Humidity().read(1), // temp/humidity
				gps.date.day(), gps.date.month(), gps.date.year(), // date
				gps.time.hour(), gps.time.minute(), gps.time.second(), // time
				gps.location.lng(), gps.location.lat()); // long/lat 
	}

	delay(10);
}
