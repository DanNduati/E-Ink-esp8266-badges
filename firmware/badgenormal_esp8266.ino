//This is the normal board
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <Arduino_JSON.h>
#include "ESPAsyncWebServer.h"
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

AsyncWebServer server(80); //Server on port 80
AsyncEventSource events("/events");

JSONVar special_msg; //json variable to store new special messages

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
    String jname = "sm"+String(numberOfElements);
    special_msg[jname] = incomingData.special_name;
    String jsonString = JSON.stringify(special_msg);
    Serial.println(jsonString);
    events.send(jsonString.c_str(), "new_special_message", millis());
  }
  //print special names
  Serial.println("Special names obtained: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(i + 1);
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
  //this function also adds the special message to the json object to be passed to the webserver
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


  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", MAIN_page);
  });

  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  server.begin();
}

void loop() {
  static unsigned long lastEventTime = millis();
  static const unsigned long EVENT_INTERVAL_MS = 5000;
  if ((millis() - lastEventTime) > EVENT_INTERVAL_MS) {
    events.send("ping", NULL, millis());
    lastEventTime = millis();
  }
}
