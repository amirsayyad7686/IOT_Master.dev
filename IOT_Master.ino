
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
            const char* ssid = <Wifi SSID>;
            const char* pass = <Wifi Pass>;
            String USER_ID = <User Id>;
            String NODE_ID = <Node Id>;
            String NODE_NAME = <Node Name>;

            void setup() {
            Serial.begin(115200);

            //GPIO modify your gpio as you wish 
		pinMode(<GPIO>, OUTPUT);
        	gpioMappings[<Component Id>] = <GPIO>;

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
                socketIO.begin("iot-master.dev", 80, "/socket.io/?EIO=4");

                // event handler
                socketIO.onEvent(socketIOEvent);
            }

            void loop() {
            //<iot-master>
            uint64_t now = millis();//dont change this timer it may make your panel slower or getting limit rate exceeded!!!
                socketIO.loop();//main websocket loop
                IOT_Master();//main iot master loop
                    if (now - sensor > 10000){//dont make it less than 10secs it may make your panel slower or getting limit rate exceeded!!!
                    sensor = now;
                   sendSensorData(<component id>, <replace 'random' with your input sensor; it should be an int>);
                }
            //</iot-master>

            // your more codes goes here !! and be careful don't use delay on your code it has effect in your iot panel
            }
            
