/*
 * OTA - Over-The-Air Update
 *
 * Konsep:
 * Update firmware ESP32 melalui jaringan WiFi
 *
 * Komponen:
 * - ESP32
 *
 * Pinout:
 * - Tidak ada pin khusus
 */

#include <WiFi.h>
#include <ArduinoOTA.h>

// ==============================
// WiFi
// ==============================
const char* ssid = "Wokwi-GUEST";
const char* password = "";

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("ESP32 OTA Demo");
  Serial.println("================================");

  // ==============================
  // Connect WiFi
  // ==============================
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // ==============================
  // OTA Configuration
  // ==============================
  ArduinoOTA.setHostname("ESP32-OTA");

  ArduinoOTA.setPassword("admin");

  ArduinoOTA.onStart([]() {
    Serial.println("OTA Update Started");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA Update Finished");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf(
      "Progress: %u%%\r",
      (progress / (total / 100))
    );
  });

  ArduinoOTA.onError([](ota_error_t error) {

    Serial.printf("OTA Error[%u]: ", error);

    if (error == OTA_AUTH_ERROR) {
      Serial.println("Authentication Failed");
    }
    else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connection Failed");
    }
    else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();

  Serial.println("OTA Ready!");
  Serial.println("Hostname: ESP32-OTA");
  Serial.println("Password: admin");
}

void loop() {

  // Handle OTA request
  ArduinoOTA.handle();

}
