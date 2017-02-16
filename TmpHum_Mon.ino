/**
 * @file: TmpHum_Mon.ino
 * @purpose: allows for collection of temperature and humidity data using the SHT30A-EASY
 * @author: Christopher Naron
 */

void setup() {
  // Initialize serial input with a poling rate of 9600.
  const int POLLING_RATE = 9600;
  Serial.begin(POLLING_RATE);
}

void loop() {
  // Initialize sensors.
  int tempSerial = analogRead(A0);
  int humiditySerial = analogRead(A1);
  const float VDD = 3.3;  // 3.3V inut from board. Used in conversions.

  // convert analog to digital
  float tempVoltage = analogToDigital(tempSerial);
  float humidityVoltage = analogToDigital(humiditySerial);

  // Spec sheet voltage -> temperature/humidity conversions.
  // http://www.mouser.com/ds/2/682/Sensirion_Humidity_SHT3x_Datasheet_analog-767292.pdf
  float temperature = -88.375 + (393.75 * (tempVoltage / VDD));  // fahrenheit by default
  float humidity = -12.5 + (125 * (humidityVoltage / VDD));

  const bool celsius = false;  // set true to switch to celsius.
  dataOutput(temperature, humidity, celsius);
  delay(1000);
}

/**
 * analogToDigital converts the 10 bit analog input into a voltage
 *  output for further calculations.
 * @param sensor. int current sensor analog value from analogRead.
 * @return float. Current voltage.
 */
float analogToDigital(int sensorValue) {
  const float BASE_VOLTAGE = 5.0;
  const int ANALOG_RANGE = 1023;
  return sensorValue * (BASE_VOLTAGE / ANALOG_RANGE);  // standard ADC formula.
}

/**
 * dataOuput prints the current values to the serial monitor
 *  mostly used as an organization tool.
 * @param temperature. float containing current temperature.
 * @param humidity. float containing current humidity percent.
 * @param celcius. bool that sets format to celcius when true.
 *   Default value = false.
 * @return none
 */
void dataOutput(float temperature, float humidity, bool celcius) {
  // Initialize strings/chars for output.
  const char PCNT = 37;  // percent ascii code. Used in output formatting.
  const char DEG = 176;  // ° symbol. Used in output formatting
  const String TEMP_STR = "Temperature: ";
  const String HUMID_STR = "\tHumidity: ";
  const String FAHRENHEIGHT = " F";
  const String CELSIUS = " C";
  // add a degree symbol to temperature units to remove any ambiguity.
  CELSIUS += DEG;
  FAHRENHEIGHT += DEG;

  if (celcius == true){
    temperature = (temperature - 32) * 5/9; // convert to celsius.
    Serial.println(TEMP_STR + temperature + CELSIUS + HUMID_STR + humidity +
                   PCNT);
  }
  else{
    Serial.println(TEMP_STR + temperature + FAHRENHEIGHT + HUMID_STR +
                   humidity + PCNT);
  }
}
