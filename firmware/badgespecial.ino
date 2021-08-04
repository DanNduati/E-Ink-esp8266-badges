//This is the special board
//has two names from the list scrolling on the screen
#include <esp_now.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include "names.h"

//The mac adresses of the receivers -> strore them in a 2d array
//to make registering peers easier
uint8_t broadcastAddresses[4][6] = {
  {0x30, 0xAE, 0xA4, 0x18, 0x1C, 0x58},
  {0xF0, 0xFF, 0x2F, 0x4D, 0x3C, 0xFF},
  {0xF0, 0xFF, 0x2F, 0x4D, 0x3C, 0xCF},
  {0x4A, 0x7E, 0xA2, 0x2F, 0x1C, 0x58}
};

//variable will store a success message if payload was delivered to the recepient
String success_msg;

//payload to be sent
typedef struct struct_message {
  //two special names that will be transmitted by this special board
  char *name1;
  char *name2;
} struct_message;

// Create a struct_message to be sent to normal boards
struct_message myData;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status normal board address: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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
#ifdef ESP32

#else
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
#endif
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peers
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  //dynamically add all peers in the broadcast array
  for (int i = 0; i < 4; i++) {
    memcpy(peerInfo.peer_addr, broadcastAddresses[i], 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Failed to add normal board");
      return;
    }
  }
}

void loop() {
  //assign two special names to be transmitted by this special board
  myData.name1 = "Winston Smith";
  myData.name2 = "Ronald Greene";

  //display a random name from the liston the e-ink
  int index = random(0, 297);

  //display the list of names on the serial monitor
  Serial.println("------------------------------------");
  Serial.println("          Never forgotten           ");
  Serial.println("------------------------------------");
  for (int i = 0; i < 297; i++) {
    Serial.println(names_to_be_displayed[i]);
  }
  Serial.println("ready to send data to the normal boards!");
  //send message via ESP-NOW
  esp_err_t result = esp_now_send(0, (uint8_t *)&myData, sizeof(myData));
  delay(5000);
}
