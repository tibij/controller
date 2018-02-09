#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4      // DS18B20 pin

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void setupOneWireBus() {
  // setup OneWire bus
  DS18B20.begin();
}

String getTemperature() {  
  Serial.print("Requesting DS18B20 temperature...");
  float readTemperature;
  int resolution;

  do {
    
    DS18B20.setResolution(12);
    resolution = DS18B20.getResolution();
    Serial.print("Resolution: ");
    Serial.println(resolution);
    DS18B20.requestTemperatures();
    delay(100);
    readTemperature = DS18B20.getTempCByIndex(0);
    Serial.println(readTemperature);
    delay(1000);
  } while (readTemperature == 85.0 || readTemperature == (-127.0));

  // Convert temperature to a string with two digits before the comma and 2 digits for precision
  char convertedTemperature[6];
  dtostrf(readTemperature, 2, 2, convertedTemperature);
  return (String)convertedTemperature;
}
