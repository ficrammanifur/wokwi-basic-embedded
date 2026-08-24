/*
 * WiFi - WiFi Connection
 * 
 * Konsep: Menghubungkan ESP32 ke jaringan WiFi
 * 
 * Komponen:
 * - ESP32 dengan WiFi
 * 
 * Pinout:
 * - Tidak ada pin khusus untuk WiFi
 */

#include <WiFi.h>

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

void setup() {
  Serial.begin(115200);
  
  Serial.println("WiFi Demo Started");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}

void loop() {
  // Cek status WiFi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi disconnected, attempting to reconnect...");
    WiFi.reconnect();
  }
  
  delay(5000);
}
