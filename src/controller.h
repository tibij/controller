#include <Arduino.h>

#ifndef CONTROLLER_H
#define CONTROLLER_H

//#define GAZ 1
#define ELECTRIC 1
#define START_TEMPERATURE 30

// Set output GPIOs
const int releuCentralaElectrica = 32;
const int releuCentralaGaz = 33;

const int releuPompaParter = 17;
const int releuPompaEtaj = 19;
const int releuPompaPardoseala = 22;
const int releuPompaBoiler = 25;

const int vana3cai = 27;

//const int oneWireBus = 4;

// Set input GPIOs
const int termostatParter = 14;
const int termostatEtaj = 21;
const int termostatCentralaLemne = 23;


// Topics defined on the MQTT broker

const char* mqttTopicPufferTemperaturaTur = "house/demisol/centrala/puffer/tempTur/value";

const char* mqttTopicCentralaElectrica = "house/demisol/centrala/electrica/state";
const char* mqttTopicCentralaGaz = "house/demisol/centrala/gaz/state";
const char* mqttTopicCentralaLemne = "house/demisol/centrala/lemn/state";

const char* mqttTopicTermostatParter = "house/parter/dinning/termostat/state";
const char* mqttTopicTermostatEtaj = "house/etaj/anda/termostat/state";

const char* mqttTopicPompaParter = "house/demisol/centrala/pompaParter/state";
const char* mqttTopicPompaEtaj = "house/demisol/centrala/pompaEtaj/state";
const char* mqttTopicPompaPardoseala= "house/demisol/centrala/pompaDemisolPardoseala/state";
const char* mqttTopicPompaBoiler = "house/demisol/centrala/pompaBoiler/state";

void publishMQTT(const char* mqttTopic, String value);
int checkMQTT();
String getTemperature(float& readTemperature);

#endif