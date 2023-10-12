
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
            const char* ssid = "A34";
            const char* pass = "24683579";
            String USER_ID = "651d6d338c92523b5492e870";
            String NODE_ID = "3f8a4083-3167-4573-962a-9ac63c6df535";
            String NODE_NAME = "aasdasdasd";

            void setup() {
            Serial.begin(115200);

            //GPIO modify your gpio as you wish 
                    gpioMappings["651d6e068c92523b5492e876"] = 1;// Toggle - component name : aaaaaaaaaaaaaaaaaa
				gpioMappings["651d74088c92523b5492e91e"] = 2;// Toggle - component name : asdasdsadsad
				gpioMappings["651d74228c92523b5492e927"] = 3;// Slider - component name : adssadsad
				

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
                socketIO.begin("192.168.139.64", 5101, "/socket.io/?EIO=4");

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
                    sendSensorData("651d6e168c92523b5492e879",random(50));//replace random with you favorite signal , Sensor Name : sssssssssssssss
				sendSensorData("651d6e258c92523b5492e87c",random(50));//replace random with you favorite signal , Sensor Name : sdddddddddddddddddddd
				sendSensorData("651d80338c92523b5492e9bf",random(50));//replace random with you favorite signal , Sensor Name : home temp
				
                    
                }
            //</iot-master>

            // your more codes goes here !! and be careful don't use delay on your code it has effect in your iot panel
            }
            
