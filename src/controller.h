#ifndef CONTROLLER_H
#define CONTROLLER_H

//#define GAZ 1
#define ELECTRIC 1

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
const char* mqttTopicTemp = "/a/b14603c1-f4a9-4bab-9b56-ecb40281c24a/p/6533/d/3369edd9-5936-4422-99ad-d743a4f95f76/sensor/Temp/data";
const char* mqttTopicCentralaElectrica = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/cElectr/state";
const char* mqttTopicCentralaGaz = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/cGaz/state";
const char* mqttTopicCentralaLemne = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/cLemne/state";

const char* mqttTopicTermostatParter = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/tParter/state";
const char* mqttTopicTermostatEtaj = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/tEtaj/state";

const char* mqttTopicPompaParter = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/pParter/state";
const char* mqttTopicPompaEtaj = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/pEtaj/state";
const char* mqttTopicPompaPardoseala = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/pFloor/state";
const char* mqttTopicPompaBoiler = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/actuator/pBoiler/state";

const char* mqttTopicTemperaturaTur = "/a/06e2cfa4-e88b-45d8-aa9f-017c3e592a0c/p/14787/d/32a33b54-41e7-4da9-bdb9-7715e7ff9c2a/sensor/Temp/data";

void publishMQTT(const char* mqttTopic, String value, int isSensor);
int checkMQTT();
String getTemperature();

#endif