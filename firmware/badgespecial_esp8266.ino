#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <espnow.h>
#include "index_special.h" //Our HTML webpage contents

/* Put your SSID & Password */
const char* ssid = "SpecialBadge";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

//device IP
IPAddress local_ip(192, 168, 1, 123);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80); //Server on port 80

void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

//The special name sent by this board
String sname = "BIC_FOUNDED_2018";

//The mark adresses of the receivers -> strore them in a 2d array
//to make registering peers easier
uint8_t broadcastAddresses[4][6] = {
  {0x30, 0xAE, 0xA4, 0x18, 0x1C, 0x58},
  {0xF0, 0xFF, 0x2F, 0x4D, 0x3C, 0xFF},
  {0x60, 0x01, 0x94, 0x24, 0xFA, 0x89},
  {0x4A, 0x7E, 0xA2, 0x2F, 0x1C, 0x58}
};

//variable will store a success message if payload was delivered to the recepient
String success_msg;

//payload to be sent
typedef struct struct_message {
  //two special names that will be transmitted by this special board
  char special_name[40];
} struct_message;

// Create a struct_message to be sent to normal boards
struct_message myData;

long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between serial print and data sends

// callback when data is sent
void OnDataSent(uint8_t *mac_addr,  uint8_t sendStatus) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status normal board address: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid);
  
  delay(100);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Register peers
  //dynamically add all peers in the broadcast array
  for (int i = 0; i < 4; i++) {
    esp_now_add_peer(broadcastAddresses[i], ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  }

  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if (millis() - lastSendTime > interval) {
    //assign  special name to be transmitted by this special board
    sname.toCharArray(myData.special_name, 40);
    Serial.println("ready to send data to the normal boards!");
    //send message via ESP-NOW
    //esp_now_send(0, (uint8_t *)&myData, sizeof(myData));
    for (int i = 0; i < 4; i++) {
      esp_now_send(broadcastAddresses[i], (uint8_t *) &myData, sizeof(myData));
    }
    lastSendTime = millis();
  }
}
