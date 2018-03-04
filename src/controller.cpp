#include <Arduino.h>

#include "controller.h"

// Parametri de stare termostate
int stareNouaTermostatParter;
int stareCurentaTermostatParter = 0;

int stareNouaTermostatEtaj;
int stareCurentaTermostatEtaj = 0;

int stareNouaTermostatCentralaLemne;
int stareCurentaTermostatCentralaLemne = 0;

// Parametri de stare centrale
int stareCentralaElectrica = 0;
int stareCentralaGaz = 0;
int stareCentralaLemne = 0;

// Parametri de stare pompe
int starePompaParter = 0;
int starePompaEtaj = 0;
int starePompaPardoseala = 0;
int starePompaBoiler = 0;

// Sensori de temperatura
String temperaturaTur;
float readTemperature;

void setupGPIOs(){
    pinMode(releuCentralaElectrica, OUTPUT);   
    pinMode(releuCentralaGaz, OUTPUT);
    pinMode(releuPompaParter, OUTPUT);
    pinMode(releuPompaEtaj, OUTPUT);
    pinMode(releuPompaPardoseala, OUTPUT);
    pinMode(releuPompaBoiler, OUTPUT);
    pinMode(vana3cai, OUTPUT);

    pinMode(termostatParter, INPUT);
    pinMode(termostatEtaj, INPUT);
    pinMode(termostatCentralaLemne, INPUT);

    // Setam starea initiala a pompelor ca oprite (HIGH = OPRIT)
    digitalWrite(releuPompaParter, HIGH);
    digitalWrite(releuPompaEtaj, HIGH);
    digitalWrite(releuPompaPardoseala, HIGH);
    digitalWrite(releuPompaBoiler, HIGH);
    digitalWrite(vana3cai, HIGH);
}

void verificaTermostate(){
    // Citeste stare termostat parter
    stareNouaTermostatParter = digitalRead(termostatParter);
    Serial.print("Stare termostat parter: ");
    Serial.println(stareNouaTermostatParter);

    // Citeste stare termostat etaj
    stareNouaTermostatEtaj = digitalRead(termostatEtaj);
    Serial.print("Stare termostat etaj: ");
    Serial.println(stareNouaTermostatEtaj);

    // Citeste stare termostat centrala pe lemne
    stareNouaTermostatCentralaLemne = digitalRead(termostatCentralaLemne);
    Serial.print("Stare termostat centrala lemne: ");
    Serial.println(stareNouaTermostatCentralaLemne);
}

void verificaTemperatura() {
    temperaturaTur = getTemperature(readTemperature);
}

// Control centrale. Se opresc sau pornesc in functie de starile termostatelor si temperatura tur puffer
void controlCentrale(){ 
    
    int temperaturaPufferOK = 0;
    
    // Verificam daca sensorul de temperatura este in parametrii
    if ((readTemperature != -127) && (readTemperature != 85))
        if (readTemperature > START_TEMPERATURE)
            temperaturaPufferOK = 1;     
    else
        // Sensor de temperatura nefunctional ne bazam numai pe termostatul de contact
        if (stareNouaTermostatCentralaLemne)
            temperaturaPufferOK = 1;
 
    if (!temperaturaPufferOK){
        stareCentralaLemne = 0;
        Serial.println("Nu merge centrala pe lemne");
        // Daca centrala pe lemne nu merge se verifica daca trebuie pornita centrala electrica sau cea pe gaz
        if (stareNouaTermostatEtaj || stareNouaTermostatParter ){
            #ifdef GAZ
                digitalWrite(releuCentralaGaz, HIGH);
                stareCentralaGaz = 1;
                Serial.println("Centrala gaz: PORNITA");
            #endif
            #ifdef ELECTRIC
                digitalWrite(releuCentralaElectrica, HIGH);
                stareCentralaElectrica = 1;
                Serial.println("Centrala electrica: PORNITA");
            #endif
        }
        // Oprim centrala care merge
        else {
            #ifdef GAZ
                digitalWrite(releuCentralaGaz, LOW);
                stareCentralaGaz = 0;
                Serial.println("Centrala gaz: OPRITA");
            #endif
            #ifdef ELECTRIC
                digitalWrite(releuCentralaElectrica, LOW);
                stareCentralaElectrica = 0;
                Serial.println("Centrala electrica: OPRITA");
            #endif           
        }
    }
    else {
        // Ne asiguram ca daca merge centrala pe lemne cel de gaz sau electric sunt oprite
        stareCentralaLemne = 1;
        Serial.println("Centrala pe lemne: PORNITA");
        #ifdef GAZ
            digitalWrite(releuCentralaGaz, LOW);
            stareCentralaGaz = 0;
            Serial.println("Centrala gaz: OPRITA");
        #endif
        #ifdef ELECTRIC
                digitalWrite(releuCentralaElectrica, LOW);
                stareCentralaElectrica = 0;
                Serial.println("Centrala electrica: OPRITA");
        #endif        
    }
}
// Functie de control incalzire parter
void controlParter(){   
    // Compara starea anterioara cu starea citita
    if (stareCurentaTermostatParter != stareNouaTermostatParter)
        // Incalzire etaj ON
        if (stareNouaTermostatParter){
            // Pornim pompa parter
            digitalWrite(releuPompaParter, LOW);
            starePompaParter = 1;
        }
        // Incalzire parter OFF
        else {
            // Oprim pompa parter
            digitalWrite(releuPompaParter, HIGH);
            starePompaParter = 0;
        }
}

// Functie de control incalzire etaj
void controlEtaj(){   
    // Compara starea anterioara cu starea citita
    if (stareCurentaTermostatEtaj != stareNouaTermostatEtaj)
        // Incalzire etaj ON
        if (stareNouaTermostatEtaj){
            // Pornim pompa etaj
            digitalWrite(releuPompaEtaj, LOW);
            starePompaEtaj = 1;
        // Incalzire etaj OFF
        }
        else {
            // Oprim pompa etaj
            digitalWrite(releuPompaEtaj, HIGH);
            starePompaEtaj = 0;
        }
}

// Functie de control incalzire pardoseala
void controlPardoseala(){   
    // Verifica daca exista cerere de incalzire la etaj sau la parter
    if (stareCurentaTermostatParter || stareCurentaTermostatEtaj){
        // Etajul sau parterul sunt incalzite. Pornim pompa pardoseala
        digitalWrite(releuPompaPardoseala, LOW);
        starePompaPardoseala = 1;
        // Aici va trebui trimis un semnal la etaj sa porneasca pompa de la distribuitor
    }
    else {
        // Oprim pompa pardoseala
        digitalWrite(releuPompaPardoseala, HIGH);
        starePompaPardoseala = 0;
        // Aici va trebui trimis un semnal la etaj sa opreasca pompa de la distribuitor
    }
}

void controlBoiler() {
    
    int temperaturaPufferOK = stareCentralaLemne && (readTemperature > 45) && (readTemperature != 85);

    if ( temperaturaPufferOK  || stareCentralaGaz || stareCentralaElectrica) {
        digitalWrite(releuPompaBoiler, LOW);
        starePompaBoiler = 1;
        Serial.println("Boiler: PORNIT");
    }
    else {
        digitalWrite(releuPompaBoiler, HIGH);
        starePompaBoiler = 0;
        Serial.println("Boiler: OPRIT");
    }
}

void salveazaStareTermostate(){
    stareCurentaTermostatParter = stareNouaTermostatParter;
    stareCurentaTermostatEtaj = stareNouaTermostatEtaj;
    stareCurentaTermostatCentralaLemne = stareNouaTermostatCentralaLemne;
}

void publicaStareaActuala() {
 
    String centralaElectrica(stareCentralaElectrica);
    String centralaGaz(stareCentralaGaz);
    String centralaLemne(stareCentralaLemne);

    String stareTermostatParter(stareCurentaTermostatParter);
    String stareTermostatEtaj(stareCurentaTermostatEtaj);
    
    String pompaParter(starePompaParter);
    String pompaEtaj(starePompaEtaj);
    String pompaPardoseala(starePompaPardoseala);
    String pompaBoiler(starePompaBoiler);
    
    // Publish only if we have connection to MQTT broker
    int isConnected = checkMQTT();
    if (isConnected) {
        publishMQTT(mqttTopicCentralaElectrica, centralaElectrica);
        publishMQTT(mqttTopicCentralaGaz, centralaGaz);
        publishMQTT(mqttTopicCentralaLemne, centralaLemne);

        publishMQTT(mqttTopicTermostatParter, stareTermostatParter);
        publishMQTT(mqttTopicTermostatEtaj, stareTermostatEtaj);

        publishMQTT(mqttTopicPompaParter, pompaParter);
        publishMQTT(mqttTopicPompaEtaj, pompaEtaj);
        publishMQTT(mqttTopicPompaPardoseala, pompaPardoseala);
        publishMQTT(mqttTopicPompaBoiler, pompaBoiler);

        publishMQTT(mqttTopicPufferTemperaturaTur, temperaturaTur);
    }
}