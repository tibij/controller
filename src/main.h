// Main.h

void setupGPIOs();
int setupWiFi();
void setupMQTT();
void setupOneWireBus();

void verificaTermostate();
void verificaTemperatura();
void controlCentrale();
void controlParter();
void controlEtaj();
void controlPardoseala();
void controlBoiler();
void salveazaStareTermostate();
void publicaStareaActuala();

String getTemperature();
