/*
 * OTA - Over-The-Air Update
 * 
 * Konsep: Update firmware melalui jaringan
 * 
 * Komponen:
 * - ESP32 dengan WiFi
 * 
 * Pinout:
 * - Tidak ada pin khusus
 */

#include <WiFi.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  
  Serial.println("OTA Demo Started");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Start OTA server
  AsyncElegantOTA.begin(&server);
  server.begin();
  
  Serial.println("OTA server started");
  Serial.println("Access: http://" + WiFi.localIP().toString() + "/update");
  Serial.println("Username: admin, Password: admin (default)");
}

void loop() {
  AsyncElegantOTA.loop();
}
