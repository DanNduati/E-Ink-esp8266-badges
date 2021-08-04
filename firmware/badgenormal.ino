//This is the normal board
//has 10 names scrolling on the screen
#include <esp_now.h>
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include "names.h"

//payload to be received from a special board
typedef struct struct_message {
  char *name1;
  char *name2;
} struct_message;
//struct_messsage to hold incoming data
struct_message incomingData;


// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *receivedData, int len) {
  memcpy(&incomingData, receivedData, sizeof(incomingData));
  Serial.print("Data received!");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println("names from the special badge");
  Serial.print("name1: ");
  Serial.println(incomingData.name1);
  Serial.print("name2: ");
  Serial.println(incomingData.name2);
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
