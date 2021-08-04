//This is the normal board
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "names.h"


//payload to be received from a special board
typedef struct struct_message {
  //two special names that will be transmitted by this special board
  char special_name[40];
} struct_message;
//struct_messsage to hold incoming data
struct_message incomingData;

long lastSendTime = 0;        // last send time
int interval = 10000;          // interval between name prints

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *receivedData, uint8_t len) {
  memcpy(&incomingData, receivedData, sizeof(incomingData));
  Serial.println("Obtained name from special badge!");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Special name from the special badge: ");
  Serial.println(incomingData.special_name);
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  if (millis() - lastSendTime > interval) {

    //display the list of names on the serial monitor
    Serial.println("------------------------------------");
    Serial.println("          Never forgotten           ");
    Serial.println("------------------------------------");
    for (int i = 0; i < 297; i++) {
      Serial.println(names_to_be_displayed[i]);
    }
    lastSendTime = millis();
  }
}
