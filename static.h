// WebSocketHandler.h
#ifndef STATIC_H
#define STATIC_H
#include <map>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <ArduinoJson.h>
extern SocketIOclient socketIO;
// Declare global variable for gpioMappings
extern std::map<String, int> gpioMappings;
extern String USER_ID;
extern String NODE_ID;
extern String NODE_NAME;
extern String webSerialData;
extern unsigned long sensor;

extern String eventData;

void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length);
void createJsonMessage(const String& message, const std::map<String, String>& params);
void controlGPIO(const char* componentId, int componentValue, const char* componentType);
void restartProccess(const char* nodeId, const char* userId);
void checkConnectionProccess(const char* nodeId, const char* userId);
void processReceivedData(const JsonObject& jsonData);
void sendSensorData(const char* componentId, int componentValue);
void webSerial(const String& message);
void IOT_Master();
void startUp();
#endif
