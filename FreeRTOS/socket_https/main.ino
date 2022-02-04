
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>

// Certificado necessário para conexão SSL
const char *ca = 
    "-----BEGIN CERTIFICATE-----\n" \
    "          Your_certificate              \n" \
    "-----END CERTIFICATE-----\n";

WiFiMulti wifiMulti;

#define WIFI_SSID "your_SSID"
#define WIFI_PASSWORD "your_PASSWORD"
bool send = true;

void setup() {
  Serial.begin(115200);
  Serial.println();
  for (uint8_t t = 3; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush(); // Aguarda a conclusão da transmissão e limpa a serial
    delay(1000);
  }
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD); // Conecta-se ao AP
}

void loop() {
  if (wifiMulti.run() ==
      WL_CONNECTED) { // Verifica se está conectado à internet
    HTTPClient http;
    if (send) {
      Serial.println("[HTTP] begin...");
      http.begin("https://www.geniot.com.br/things/services/api/v1/variables/"
                 "S00/value/?token=your_token",
                 ca);
      // Adição de cabeçalhos para a requisição
      http.addHeader("Content-Type", "application/json");
      http.addHeader("HOST", "geniot.com.br");
      http.addHeader("Connection", "close");

      int httpCodeResponse = http.POST(
          "{\"value\": 56.8}"); // Armazena o código de resposta da requisição

      if (httpCodeResponse > 0) {
        Serial.printf("[HTTP] response code: %d\n", httpCodeResponse);

        // Se a resposta for 200 OK, imprime a resposta
        if (httpCodeResponse == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] Error: %s\n",
                      http.errorToString(httpCodeResponse).c_str());
      }

      http.end();
      send = false;
    }
  }
}
