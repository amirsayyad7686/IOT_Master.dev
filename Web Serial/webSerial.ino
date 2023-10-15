
#include "static.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <map>
std::map<String, int> gpioMappings;
//user config
const char* ssid = "SSID";
const char* pass = "PASS";
String USER_ID = "USERID";
String NODE_ID = "NODEID";
String NODE_NAME = "NODENAME";
//webSerialData string object for using web serial API
String webSerialData = "";
void setup() {
Serial.begin(115200);
pinMode(LED_BUILTIN,OUTPUT);

    for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...", t);
    Serial.flush();
        delay(1000);
    }

    // Connect to Wi-Fi
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    String ip = WiFi.localIP().toString();
    Serial.printf("[SETUP] WiFi Connected %s", ip.c_str());

    // server address, port and URL
    socketIO.begin("iot-master.ir", 80, "/socket.io/?EIO=4");

    // event handler
    socketIO.onEvent(socketIOEvent);
}

void loop() {
//<iot-master>
IOT_Master();//main iot master loop
//</iot-master>
    //this is a simple test for Web Serial API
if(webSerialData == "ON"){
    digitalWrite(LED_BUILTIN, HIGH);
    webSerial("LED has turned on");
}else if(webSerialData == "OFF"){
  digitalWrite(LED_BUILTIN, LOW);  
    webSerial("LED has turned off");
}
// your more codes goes here !! and be careful don't use delay on your code it has effect in your iot panel
}
