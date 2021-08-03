//lolin esp32 board code
#include <esp_now.h>
#include <WiFi.h>

//MAC adress of the receiver
uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x18, 0x1C, 0x58};
//variable will store a success message if payload was delivered to the recepient
String success_msg;

//payload to be sent
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
// Create a struct_message to be sent to peers
struct_message myData;
//struct_messsage to hold incoming data
struct_message incomingData;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) {
    success_msg = "Delivery Success :)";
  }
  else {
    success_msg = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *receivedData, int len) {
  memcpy(&incomingData, receivedData, sizeof(incomingData));
  Serial.print("Data received!");
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(incomingData.a);
  Serial.print("Int: ");
  Serial.println(incomingData.b);
  Serial.print("Float: ");
  Serial.println(incomingData.c);
  Serial.print("Bool: ");
  Serial.println(incomingData.d);
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

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer(pair)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Set values to send
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1, 20);
  myData.c = 1.2;
  myData.d = false;
  Serial.println("ready to send dat to peers!");
  //send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, 1);
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
  /*
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) badgeid,7);
    if (result == ESP_OK) {
    Serial.println("Sent with success");
    }
    else {
    Serial.println("Error sending the data");
    }

    //display received payload
    Serial.print("Incoming: ");
    Serial.println(incoming);
    delay(2000);*/
}
