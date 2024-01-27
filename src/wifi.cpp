#include <Arduino.h>
#include <WiFi.h>

// WiFi Credentials
const char* ssid = "cgrn";
const char* password = "monchiX2";


int setupWiFi() {    
    delay(10);
    
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    
    // Loop until we connected but stop after 10 attempts
    int retryCount = 0;
    while ( (WiFi.status() != WL_CONNECTED) && retryCount < 10 ) {
        delay(500);
        Serial.print(".");
        retryCount++;
    }

    int wifiStatus = WiFi.status();
    switch (wifiStatus) {
        case WL_CONNECTED:
            Serial.println("");
            Serial.print("WiFi connected. ");
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            break;
        default:
            Serial.println("");
            Serial.println("WiFi connection failed.");
            break;
    }
    
    return wifiStatus;
}