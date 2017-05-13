# Arduino Sensor Collection
-----------------------
#### Basic Requirements
- Arduino Uno
- SHT30A analog temperature and humidity sensor
- Adafruit Ultimate GPS Logger Shield

#### Usage
- Temperature data collection: `Temperature().read( TEMPERATURE_PIN );`
- Humidity data collection: `Humidity().read( HUMIDITY_PIN );`
- TinyGPS usage can be found [Here](http://arduiniana.org/libraries/tinygpsplus/).
- Data Logging to SD: ```SDLog( temperatureData, humidityData, day, month, year, hour, minute, second, longitude, latitude )``` Please note that the day, month, year, etc must be of type `TinyGPSPlus`. temperatureData must be of type `Temperature`, and humidityData of type `Humidity`
- If using the included `main.ino` file, the analong pins may be adjusted using the included `TEMP_PIN` and `HUMIDITY_PIN` constants at the top of the file.

-------------------
##### Dependencies:
[TinyGPS++](https://github.com/mikalhart/TinyGPSPlus) is used to parse NMEA Sentences.
