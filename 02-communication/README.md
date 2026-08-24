# 02 — Communication

Mempelajari cara ESP32 berkomunikasi dengan perangkat lain maupun jaringan menggunakan berbagai protokol komunikasi.

**Materi:** UART • I2C • SPI • WiFi • MQTT

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | UART | Komunikasi serial asinkron |
| 02 | I2C | Komunikasi dua kabel dengan sensor |
| 03 | SPI | Komunikasi berkecepatan tinggi |
| 04 | WiFi | Koneksi ESP32 ke jaringan |
| 05 | MQTT | Komunikasi IoT publish/subscribe |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **Komunikasi UART** - Berkomunikasi dengan perangkat serial
2. **Komunikasi I2C** - Menghubungkan sensor I2C
3. **Komunikasi SPI** - Menggunakan protokol SPI
4. **Koneksi WiFi** - Menghubungkan ESP32 ke internet
5. **MQTT** - Mengirim dan menerima data via MQTT

---

## 🔧 Komponen yang Digunakan

- ESP32 Dev Kit V1
- AHT20 (Sensor Suhu & Kelembaban I2C)
- MAX6675 (Sensor Thermocouple SPI)
- LED, Resistor, Button

---

## 📖 Penjelasan Setiap Materi

---

### 01-uart — UART Serial Communication

**Konsep:** Mempelajari komunikasi serial asinkron antara ESP32 dan perangkat lain menggunakan UART.

**Komponen:**
- ESP32 (UART2)

**Pinout:**
| Fungsi | GPIO | Keterangan |
|--------|------|------------|
| TX2 | 17 | Transmit |
| RX2 | 16 | Receive |

**Cara Kerja:**
1. ESP32 mengirim data melalui TX2
2. Data diterima melalui RX2
3. Protokol serial dengan baud rate 115200

**Kode Penting:**
```cpp
Serial2.begin(115200, SERIAL_8N1, RX2, TX2);
Serial2.println("Hello from UART2!");
if (Serial2.available()) {
  String data = Serial2.readStringUntil('\n');
}
```

**Output yang Diharapkan:**
```
Data sent to UART2
Received from UART2: Hello from UART2!
```

**Learning Points:**
- Konfigurasi UART (baud rate, data bit, stop bit, parity)
- TX/RX pin assignment
- Serial communication flow control

---

### 02-i2c — I2C Communication

**Konsep:** Mempelajari komunikasi I2C dengan sensor suhu dan kelembaban AHT20.

**Komponen:**
- 1x AHT20 (Sensor Suhu & Kelembaban)

**Pinout:**
| Fungsi | GPIO | Keterangan |
|--------|------|------------|
| SDA | 21 | Data |
| SCL | 22 | Clock |
| VCC | 3.3V | Power |
| GND | GND | Ground |

**Cara Kerja:**
1. Inisialisasi I2C dengan Wire library
2. Scan untuk menemukan device
3. Kirim command ke sensor
4. Baca data 6 byte dan konversi ke suhu/kelembaban

**Kode Penting:**
```cpp
Wire.begin(SDA, SCL);
Wire.beginTransmission(AHT20_ADDR);
Wire.write(0xAC); // Trigger measurement
Wire.requestFrom(AHT20_ADDR, 6);
// Baca dan konversi data
```

**Output yang Diharapkan:**
```
Found device at 0x38
Temperature: 25.34 °C | Humidity: 65.12 %
```

**Learning Points:**
- Konsep I2C (SDA, SCL, address)
- I2C scanning
- Sensor communication protocol
- Data conversion (raw to physical)

---

### 03-spi — SPI Communication

**Konsep:** Mempelajari komunikasi SPI berkecepatan tinggi dengan sensor MAX6675.

**Komponen:**
- 1x MAX6675 (Thermocouple Sensor)

**Pinout:**
| Fungsi | GPIO | Keterangan |
|--------|------|------------|
| SCK | 18 | Clock |
| MISO | 19 | Master In Slave Out |
| CS | 5 | Chip Select |
| VCC | 3.3V | Power |
| GND | GND | Ground |

**Cara Kerja:**
1. Inisialisasi SPI dengan SPI library
2. Select device dengan CS LOW
3. Transfer 16-bit data
4. Deselect device dengan CS HIGH
5. Ekstrak data suhu dari 12-bit

**Kode Penting:**
```cpp
SPI.begin(SCK, MISO, -1, CS);
SPI.setFrequency(1000000);
SPI.setDataMode(SPI_MODE0);
digitalWrite(CS, LOW);
uint16_t data = SPI.transfer16(0x0000);
digitalWrite(CS, HIGH);
float temp = ((data >> 3) & 0x0FFF) * 0.25;
```

**Output yang Diharapkan:**
```
Temperature: 28.50 °C
Temperature: 28.75 °C
```

**Learning Points:**
- Konsep SPI (SCK, MISO, MOSI, CS)
- SPI mode dan frekuensi
- Chip Select untuk multiple device
- Bit manipulation untuk ekstrak data

---

### 04-wifi — WiFi Connection

**Konsep:** Mempelajari cara menghubungkan ESP32 ke jaringan WiFi.

**Komponen:**
- ESP32 dengan WiFi

**Cara Kerja:**
1. Inisialisasi WiFi
2. Connect ke access point
3. Dapatkan IP address
4. Monitor status koneksi

**Kode Penting:**
```cpp
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
}
Serial.println(WiFi.localIP());
```

**Output yang Diharapkan:**
```
Connecting to WiFi......
Connected to WiFi!
IP Address: 192.168.1.100
MAC Address: 24:6F:28:XX:XX:XX
RSSI: -45 dBm
```

**Learning Points:**
- WiFi station mode
- WiFi connection states
- IP configuration (DHCP)
- Signal strength (RSSI)

---

### 05-mqtt — MQTT Communication

**Konsep:** Mempelajari komunikasi IoT menggunakan protokol MQTT (publish/subscribe).

**Komponen:**
- ESP32 dengan WiFi dan MQTT

**Cara Kerja:**
1. Connect ke WiFi
2. Connect ke MQTT broker
3. Subscribe ke topic
4. Publish data ke topic
5. Terima dan proses message dari broker

**Kode Penting:**
```cpp
PubSubClient client(espClient);
client.setServer(mqtt_server, mqtt_port);
client.setCallback(mqttCallback);
client.connect("ESP32Client");
client.subscribe("esp32/test");
client.publish("esp32/test", "Hello from ESP32!");
```

**Output yang Diharapkan:**
```
Connecting to MQTT...Connected!
Published: Hello from ESP32 #1
Published: Hello from ESP32 #2
Message received on topic: esp32/test
Payload: Hello from ESP32 #1
```

**Learning Points:**
- Konsep MQTT (broker, topic, publish/subscribe)
- MQTT client lifecycle
- Callback untuk menerima message
- QoS (Quality of Service)

---

## 📊 Perbandingan Protokol

| Protokol | Kecepatan | Jarak | Kabel | Penggunaan |
|----------|-----------|-------|-------|------------|
| **UART** | Sedang | Pendek | 2 | Serial debug, GPS |
| **I2C** | Rendah | Pendek | 2 | Sensor, EEPROM |
| **SPI** | Tinggi | Pendek | 3+ | Display, SD Card |
| **WiFi** | Tinggi | Jauh | 0 | Internet, IoT |
| **MQTT** | - | - | 0 | IoT, Cloud |

---

## ✅ Checklist Pemahaman

- [ ] Saya bisa berkomunikasi via UART
- [ ] Saya bisa membaca sensor I2C
- [ ] Saya bisa membaca sensor SPI
- [ ] Saya bisa menghubungkan ESP32 ke WiFi
- [ ] Saya bisa publish/subscribe MQTT
