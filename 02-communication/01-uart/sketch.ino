/*
 * UART - Serial Communication
 * 
 * Konsep: Komunikasi serial antara ESP32 dan perangkat lain
 * 
 * Komponen:
 * - ESP32 (UART2)
 * 
 * Pinout:
 * - TX2 -> GPIO 17
 * - RX2 -> GPIO 16
 */

// UART2 configuration
#define UART2_TX 17
#define UART2_RX 16
#define UART2_BAUD 115200

void setup() {
  // Serial monitor
  Serial.begin(115200);
  
  // UART2 untuk komunikasi
  Serial2.begin(UART2_BAUD, SERIAL_8N1, UART2_RX, UART2_TX);
  
  Serial.println("UART Demo Started");
  Serial.println("Kirim data ke UART2 dan lihat response");
}

void loop() {
  // Kirim data ke UART2
  Serial2.println("Hello from ESP32 UART2!");
  Serial.println("Data sent to UART2");
  
  // Cek jika ada data dari UART2
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.print("Received from UART2: ");
    Serial.println(data);
  }
  
  delay(2000);
}
