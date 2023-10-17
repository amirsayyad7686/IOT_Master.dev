
#include "static.h"
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <ArduinoJson.h>
SocketIOclient socketIO;
unsigned long connectRoom = 0;
unsigned long sensor = 0;
int startUpTimer = 0;
String eventData;




void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Disconnected!\n");
            startUpTimer = 0;
            break;
        case sIOtype_CONNECT:
            Serial.printf("[IOc] Connected to url: %s\n", payload);
            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
             eventData = String((char*) payload); // Store the payload data
            break;
        case sIOtype_ACK:
            Serial.printf("[IOc] get ack: %u\n", length);
            break;
        case sIOtype_ERROR:
            Serial.printf("[IOc] get error: %u\n", length);
            break;
        case sIOtype_BINARY_EVENT:
            Serial.printf("[IOc] get binary: %u\n", length);
            break;
        case sIOtype_BINARY_ACK:
            Serial.printf("[IOc] get binary ack: %u\n", length);
            break;
    }
}

void createJsonMessage(const String& message,  const std::map<String, String>& params) {
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    array.add(message);
    JsonObject param = array.createNestedObject();
    // Add the provided parameters to the JSON object
 for (const auto& kv : params) {
    param[kv.first] = kv.second;
  }

  String output;
  serializeJson(doc, output);
  socketIO.sendEVENT(output);
}
void webSerial(const String& message){
  std::map<String, String> param;
  param["node_id"]     = NODE_ID;
  param["user_id"]     = USER_ID;
  param["web_serial_data"]     = message;
  param["status"]     = "WebSerial";
  createJsonMessage("ESPrespond", param);
  webSerialData = "";
  return;
}
void controlGPIO(const char* componentId, int componentValue , const char* componentType) {
    // Check if the component_id exists in the map
  if(String(componentType) == "Toggle" || String(componentType) == "Button" || String(componentType) == "Slider"){
    if (gpioMappings.find(componentId) != gpioMappings.end()) {
        // Found the component_id in the mappings
        int gpioPin = gpioMappings[componentId];
        if(String(componentType) == "Toggle" || String(componentType) == "Button"){   
            if (componentValue == 1) {
                // Turn the GPIO pin on (e.g., set it HIGH)
                digitalWrite(gpioPin, HIGH);
                Serial.printf("Turning ON GPIO %d\n", gpioPin);
                std::map<String, String> param2;
                param2["componentId"]     = componentId;
                param2["user_id"]     = USER_ID;
                param2["status"]     = "OK";
                createJsonMessage("ESPrespond", param2);
                return ;
            } else if (componentValue == 0) {
                // Turn the GPIO pin off (e.g., set it LOW)
                digitalWrite(gpioPin, LOW);
                Serial.printf("Turning OFF GPIO %d\n", gpioPin);
                std::map<String, String> param3;
                param3["componentId"]     = componentId;
                param3["user_id"]     = USER_ID;
                param3["status"]     = "OK";
                createJsonMessage("ESPrespond", param3);
                return;
            } else {
                Serial.println("Invalid component_value");
            }
        }
        if(String(componentType) == "Slider"){ 
            analogWrite(gpioPin, componentValue);
            Serial.printf("Ranging ON GPIO %d Value : %d\n", gpioPin, componentValue);
            std::map<String, String> param;
            param["componentId"]     = componentId;
            param["user_id"]     = USER_ID;
            param["status"]     = "OK";
            createJsonMessage("ESPrespond", param);
            return ;
        }
    } else {
        Serial.println("Component ID not found in mappings please make sure that you have updated you codes!!!");
        std::map<String, String> param2;
        param2["componentId"]     = componentId;
        param2["user_id"]     = USER_ID;
        param2["status"]     = "ERROR";
        createJsonMessage("ESPrespond", param2);
        return ;
    }
  }
}

void restartProccess(const char* nodeId, const char* userId) {
    if(String(nodeId) == NODE_ID && String(userId) == USER_ID){
        Serial.println("Restarting in 5 seconds");
        std::map<String, String> param2;
        param2["node_id"]     = NODE_ID;
        param2["node_name"]     = NODE_NAME;
        param2["user_id"]     = USER_ID;
        param2["status"]     = "Restart";
        createJsonMessage("ESPrespond", param2);
        Serial.println("Restart Connection from server");
        delay(5000);
        ESP.restart();
    }
}
void checkConnectionProccess(const char* nodeId, const char* userId) {
    if(String(nodeId) == NODE_ID && String(userId) == USER_ID){
        std::map<String, String> param2;
        param2["node_id"]     = NODE_ID;
        param2["node_name"]     = NODE_NAME;
        param2["user_id"]     = USER_ID;
        param2["status"]     = "Check";
        createJsonMessage("ESPrespond", param2);
        Serial.println("Check Connection from server");
    }
}

void processReceivedData(const JsonObject& jsonData) {
  // Access the component_id, component_type, and component_value from the JSON data
  const char* componentId = jsonData["component_id"];
  const char* nodeId = jsonData["node_id"];
  const char* userId = jsonData["user_id"];
  const char* componentType = jsonData["component_type"];
  const char* processType = jsonData["process_type"];
  int componentValue = jsonData["component_value"];

  // Now you can use componentId and componentValue as needed for buttons, toggles, and sliders

    // Call your control function with the parsed data
    controlGPIO(componentId, componentValue, componentType);

    if(String(processType) == "restart"){
      restartProccess(nodeId,userId);
      return;
    }
    if(String(processType) == "check"){
      checkConnectionProccess(nodeId,userId);
      return;
    }
      if(String(processType) == "webSerial"){
      webSerialData = static_cast<String>(jsonData["web_serial_data"]);
      Serial.print("From IOT_Master :");
      Serial.println(webSerialData);
      return;
    }
    

    // You don't need to reset componentId and componentValue to empty strings and zero here,
    // as they are local variables and will go out of scope when this function exits.

}

void sendSensorData(const char* componentId, int componentValue) {
  std::map<String, String> param;
  param["component_id"] = componentId;
  param["component_value"] = componentValue;
  param["component_type"] = "Sensor";
  param["user_id"] = USER_ID;
  param["node_id"] = NODE_ID;
  createJsonMessage("message", param);
}
void startUp(){
   if(startUpTimer <= 1){
    startUpTimer = startUpTimer + 1;
        std::map<String, String> param;
        param["node_id"]     = NODE_ID;
        param["node_name"]     = NODE_NAME;
        param["user_id"]     = USER_ID;
        param["status"]     = "StartUp";
        createJsonMessage("message", param);
        std::map<String, String> param2;
        param2["node_id"]     = NODE_ID;
        param2["node_name"]     = NODE_NAME;
        param2["user_id"]     = USER_ID;
        param2["status"]     = "Check";
        createJsonMessage("ESPrespond", param2);
  }
}
void IOT_Master() {
  socketIO.loop();//main websocket loop
    uint64_t now1 = millis();
   if (now1 - connectRoom > 10000)
      {
          if(startUpTimer <= 1){
          connectRoom = now1;
          std::map<String, String> param1;
          param1["userId"]     = USER_ID;
          param1["nodeId"]     = NODE_ID;
          createJsonMessage("joinRoom", param1);
          startUp();
          Serial.printf("Esp has joined to room %s ",USER_ID.c_str());
        }
      }
    
        if (eventData.length() > 0) {
        // Process the payload data here
        // Parse the JSON payload
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, eventData);

        // Check for parsing errors
        if (error) {
          Serial.print("Error parsing JSON: ");
          Serial.println(error.c_str());
        } else {
          const char* incomingNodeId = doc[1]["node_id"];
          if(String(incomingNodeId) == NODE_ID){
           processReceivedData(doc[1]);

          }
          }
        // Clear the eventData variable
        eventData = "";
      }
}
