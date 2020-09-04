#include <FliteSensor.h>

//Create FliteSensor object
char color[] = "BLACK";
FliteSensor fliteSensor = FliteSensor(
  color,//This is the color of the Flite sensor (BLACK, BLUE, RED, GREEN), BLACK used in this example
  201,//This is the memory location in EEPROM for the low calibration distance
  211,//This is the memory location in EEPROM for the low calibration level
  221,//This is the memory location in EEPROM for the high calibration distance
  231,//This is the memory location in EEPROM for the high calibration level
  241);//This is the memory location in EEPROM for the zero PSI offset

void setup() {
  //Initialize serial
  Serial.begin(115200);
  //Initialize EEPROM, this will store calibration values
  EEPROM.begin(512);

  //Setup the FliteSensor sensor
  if(fliteSensor.beginSensor()){
    Serial.println("Successfully began FliteSensor sensor!");
  } else {
    Serial.println(" Error - Unsuccessful beginning FliteSensor sensor!");
  }
  
  delay(1000);

  //-------------------------------------------
  //These functions will need to be called by a calibration interface not demonstrated in this example, and will be specific to your interface
  //Calibration must be performed before sensor provides accurate gallons
  //Invoke the calibration high and calibration low functions to calibrate the level sensor
  fliteSensor.calibrateLow(0.0);
  fliteSensor.calibrateHigh(5.0);
  
  //Invoke the zeroPSI function to zero the pressure sensor to ambient pressure
  fliteSensor.calibrateZeroPSI();

  //Temperature does not require any configuration, and returns the temperature in Degrees F
  //-------------------------------------------
}

void loop() {
  //Read sensor data every 5 seconds
  delay(5000);
  //Display sensor values to console
  
  char level[4];
  dtostrf(fliteSensor.getLevel(), 1, 1, level);
  Serial.print("Level: ");
  Serial.print(level);
  Serial.println(" Gallons");

  char temperature[5];
  dtostrf(fliteSensor.getTemperature(), 1, 1, temperature);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" Deg.F");
  
  char pressure[5];
  dtostrf(fliteSensor.getPressure(), 1, 1, pressure);
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" PSI");

  Serial.println("");
}
