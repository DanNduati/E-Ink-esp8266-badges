//This is the normal board
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <espnow.h>
#include "names.h"
#include "index_normal.h" //our webpage

/* Put your SSID & Password */
const char* ssid = "NormalBoard";  // Enter SSID here
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

//payload to be received from a special board
typedef struct struct_message {
  //two special names that will be transmitted by this special board
  char special_name[40];
} struct_message;
//struct_messsage to hold incoming data
struct_message incomingData;

long lastSendTime = 0;        // last send time
int interval = 40000;          // interval between name prints

int special_message_count = 0;
String special_messages[4]; //array to store special messages obtained


void add_special_name(char spec_name[40]){
  String special = spec_name;
  bool match = false;
  //check if the special name is in the array
  for (int i = 0; i<4; i++){
    if (special.equals(special_messages[i])){
      match = true;
      break;
    }
  }
  if (!match){
    //check the number of elements currently in the array
    //this is a quick and dirty method 
    int numberOfElements = 0;
    for (int i =0; i<4; i++){
      if (special_messages[i] !=0){
        numberOfElements++;
      }
      else{
        break;
      }
    }
    //add match
    special_messages[numberOfElements] = special;
  }
  //print special names
  Serial.println("Special names obtained: ");
  for(int i=0; i<4; i++){
    Serial.print(i+1);
    Serial.print(": ");
    Serial.println(special_messages[i]);
  }
}
// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *receivedData, uint8_t len) {
  memcpy(&incomingData, receivedData, sizeof(incomingData));
  Serial.println("Obtained name from special badge!");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Special name from the special badge: ");
  Serial.println(incomingData.special_name);
  Serial.println();
  //function to check if special name is already in the special names array if not add it
  add_special_name(incomingData.special_name);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid);
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);

  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();          //Handle client requests
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
