/*
 * Stack Monitoring - Stack Monitoring
 * 
 * Konsep: Memantau penggunaan stack pada task FreeRTOS
 * 
 * Komponen:
 * - Tidak ada komponen fisik
 * 
 * Pinout:
 * - Tidak ada pin
 */

// Handle untuk task yang akan dibuat
TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=== Stack Monitoring Demo Started ===");

  // Cek stack task setup/loop (task "loopTask" bawaan Arduino)
  printStackInfo("setup()/loopTask", NULL);

  // Buat 2 task contoh dengan ukuran stack berbeda
  xTaskCreate(
    taskRingan,        // fungsi task
    "TaskRingan",      // nama task
    2048,              // ukuran stack (word/byte tergantung platform, di ESP32 = byte)
    NULL,              // parameter
    1,                 // priority
    &taskHandle1        // handle
  );

  xTaskCreate(
    taskBoros,
    "TaskBoros",
    4096,
    NULL,
    1,
    &taskHandle2
  );
}

void loop() {
  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 5000) {
    lastPrint = millis();

    Serial.println("\n================= STACK REPORT =================");

    // Stack task loop() Arduino sendiri
    printStackInfo("loopTask (Arduino)", NULL);

    // Stack task-task lain yang kita buat
    printStackInfo("TaskRingan", taskHandle1);
    printStackInfo("TaskBoros", taskHandle2);

    Serial.println("==================================================");
  }

  delay(1000);
}

// Fungsi untuk menampilkan info stack suatu task
// handle = NULL artinya task yang memanggil fungsi ini sendiri
void printStackInfo(const char* taskName, TaskHandle_t handle) {
  // uxTaskGetStackHighWaterMark mengembalikan sisa stack MINIMUM
  // yang pernah tercapai sejak task dibuat (dalam word, 1 word = 4 byte di ESP32)
  UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(handle);

  // Konversi ke byte
  size_t freeBytes = highWaterMark * sizeof(StackType_t);

  Serial.printf("[%-18s] Stack tersisa (high water mark): %6u bytes\n",
                taskName, (unsigned)freeBytes);

  // Peringatan jika stack tinggal sedikit (potensi stack overflow)
  if (freeBytes < 512) {
    Serial.printf("   >>> WARNING: Stack '%s' hampir habis! Pertimbangkan perbesar ukuran stack.\n", taskName);
  }
}

// ----------- Task Contoh 1: Penggunaan stack ringan -----------
void taskRingan(void* parameter) {
  int counter = 0;

  for (;;) {
    counter++;
    // Kerja ringan, variabel lokal sedikit
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// ----------- Task Contoh 2: Penggunaan stack lebih boros -----------
void taskBoros(void* parameter) {
  for (;;) {
    // Sengaja pakai array lokal besar untuk mensimulasikan pemakaian stack tinggi
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "Simulasi data besar di stack");

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
