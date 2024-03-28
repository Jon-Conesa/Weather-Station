#include <TSIC.h>
#include <DallasTemperature.h>
#include <Onewire.h>

// PT1000
float resistance = 1300;
float temperaturept;

// Dallas Temperature
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// TSIC Thermometer
TSIC Sensor1(8, 2); // Data line connected to pin 8 and volatge supply is connected to pin 2
uint16_t temperature1 = 0;
float Temperature_C = 0;

void setup() {
  Serial.begin(9600); // Serial connection at 9600 bits per second

  // Dallas Temperature
  sensors.begin();
}

void loop() {
  // PT1000
  int sensorValue = analogRead(1);
  float sensorValue2 = sensorValue;
  float voltage = (3.3*(sensorValue2 / 4095))*0.875;
  float thermResistance = (voltage*resistance)/(3.3-voltage);
  temperaturept = (thermResistance - 1000)/3.85;

  // Dallas Temperature
  sensors.requestTemperatures();
  float TempC = sensors.getTempCByIndex(0);

  // TSIC Thermometer
  if(Sensor1.getTemperature(&temperature1)){
    Temperature_C = Sensor1.calc_Celsius(&temperature1);
  }

  // Solar Panel Voltage
  float Solarresistance = 1600;
  int SolarsensorValue = analogRead(3);
  float SolarsensorValue2 = SolarsensorValue;
  float Solarvoltage = (3.3*(SolarsensorValue2 / 4095))*0.875;
  //float thermResistance = (voltage*resistance)/(3.3-voltage);
  //temperaturept = (thermResistance - 1000)/3.85;
  Serial.println(Solarvoltage);
  delay(2000);

  // Record Data
  //Serial.print("PT1000: ");
  Serial.print(temperaturept);
  Serial.print(", ");
  //Serial.print("Dallas Thermometer: ");
  Serial.print(TempC);
  Serial.print(",");
  //Serial.print(" TSIC Thermometer: ");
  Serial.print(Temperature_C);
  Serial.println("");
  delay(2000);
}