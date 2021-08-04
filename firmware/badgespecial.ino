//This is the special board
//has two names from the list scrolling on the screen
#include <esp_now.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include "names.h"

//The mark adresses of the receivers -> strore them in a 2d array
//to make registering peers easier
uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x18, 0x1C, 0x58};
//uint8_t broadcastAddress2[] = {0xFF, , , , , };
//uint8_t broadcastAddress3[] = {0xFF, , , , , };

//variable will store a success message if payload was delivered to the recepient
String success_msg;

//payload to be sent
typedef struct struct_message {
  String name1 = "Winston Smith" ;
  String name2 = "Ronald Greene";
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
  Serial.print(" send status:\t");
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

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peers
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add the first peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  //register second peer
  /*
    memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
    }
  */
}

void loop() {
  //display a random name from the liston the e-ink 

  //display the list of names on the serial monitor
  for(int i=0; i<297; i++){
    Serial.println(names_to_be_displayed[i]); 
  }
  Serial.println("ready to send data to peers!");
  //send message via ESP-NOW
  esp_err_t result = esp_now_send(0, (uint8_t *)&myData, sizeof(myData));
  delay(2000);
}
