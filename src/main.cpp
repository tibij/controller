#include <Arduino.h>
#include <WiFi.h>
#include "main.h"

void setup() {
    // setup serial port
    Serial.begin(115200);

    // setup device pins
    setupGPIOs();
    
    // setup WiFi
    setupWiFi();

    // setup MQTT connection
    setupMQTT();

    // setup OneWire bus for reading temperature
    setupOneWireBus();
}

void loop() {
    
    // Citeste stare termostate
    Serial.println("Verifica stare termostate ...");
    verificaTermostate();

    Serial.println("Citeste temperatura tur puffer ...");
    verificaTemperatura();
    
    // Porneste/opreste centrala electrica sau cea de gaz
    Serial.println("Setup centrale ...");
    controlCentrale();

    // Porneste/opreste pompa parter
    Serial.println("Setup pompa parter ...");
    controlParter();

    // Porneste/opreste pompa etaj
    Serial.println("Setup pompa etaj ...");
    controlEtaj();
    
    // Porneste/opreste pompa pardoseala
    Serial.println("Setup pompa pardoseala ...");
    controlPardoseala();

    // Porneste/opreste pompa boiler apa calda
    Serial.println("Setup pompa boiler ...");
    controlBoiler();
    
    Serial.println("Salveaza stare curenta termostate ...");
    salveazaStareTermostate();



    Serial.println("Publica stare curenta incalzire ...");
    publicaStareaActuala();

    delay(5000);
}