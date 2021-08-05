#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <espnow.h>
#include "index_normal.h" //Our HTML webpage contents



//board ap config
const char* ssid = "NormalBadge";
const char* password = "dandandandan";

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
int interval = 10000;          // interval between name prints

int special_message_count = 0;
String special_messages[4]; //array to store special messages obtained


void add_special_name(char spec_name[40]) {
  String special = spec_name;
  bool match = false;
  //check if the special name is in the array
  for (int i = 0; i < 4; i++) {
    if (special.equals(special_messages[i])) {
      match = true;
      break;
    }
  }
  if (!match) {
    //check the number of elements currently in the array
    //this is a quick and dirty method
    int numberOfElements = 0;
    for (int i = 0; i < 4; i++) {
      if (special_messages[i] != 0) {
        numberOfElements++;
      }
      else {
        break;
      }
    }
    //add match
    special_messages[numberOfElements] = special;
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

void setup(void) {
  Serial.begin(115200);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid);

  delay(100);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
  // Wait for connection

  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();          //Handle client requests
  
}
