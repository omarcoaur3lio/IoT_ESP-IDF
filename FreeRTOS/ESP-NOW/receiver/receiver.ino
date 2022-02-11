#include <WiFi.h>
#include <esp_now.h>

const int btnPin = 0;
int buttonState;
bool ledState = true, lastButtonState = false;         
unsigned long debounceDelay = 50, lastDebounceTime = 0, countToSend = 0, receivedValue = 0; 

uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0xF3, 0x6C, 0x94};

// Data receiving callback function
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&receivedValue, incomingData, sizeof(receivedValue));
    Serial.print("Received value: ");
    Serial.println(receivedValue);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    // char macStr[18];
    // Serial.print("Packet to: ");
    // snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0],
    //         mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    // Serial.println(macStr);
    // Serial.print("Send status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void readButtonState() {
    int reading = !digitalRead(btnPin);

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;

            if (buttonState == true) {
                ledState = !ledState;
                countToSend++;
                esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&countToSend, sizeof(countToSend));
                // if (result == ESP_OK) {
                //     Serial.println("Sent with success");
                // } else {
                //     Serial.println("Error sending the data");
                // }
            }
        }
    }
    lastButtonState = reading;
}

void setup() {
    Serial.begin(115200);
    pinMode(btnPin, INPUT);

    // initialization ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) {
      Serial.println("Error initializing ESP-NOW");
      return;
    }
    // Set the receive data callback function
    esp_now_register_recv_cb(OnDataRecv);

    esp_now_register_send_cb(OnDataSent);
    
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Failed to add peer");
      return;
    }
}

void loop() {
    readButtonState();
}