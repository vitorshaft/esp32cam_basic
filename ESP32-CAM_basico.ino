#include "esp_camera.h"
#include <WiFi.h>

//  Configuração para AI THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define LED_GPIO_NUM       4

//  Credenciais WiFi
const char* ssid = "Rede WiFi";
const char* password = "senha";

//  Protótipos
void startCameraServer();
void setupLedFlash(int pin);

void setup() {
   //  Configura Serial e debug
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  //  Aplica configuracao da camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000; //  frequencia de clock
  config.frame_size = FRAMESIZE_UXGA; //formato 1600 x 1200
  config.pixel_format = PIXFORMAT_JPEG; // para streaming

  //  Comecar com UXGA e qualidade JPEG alta, para pre-alocar um maior buffer de frame
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // Inicia camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera falhou ao iniciar, erro 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  setupLedFlash(LED_GPIO_NUM);

  //  Inicia conexão WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  startCameraServer();

  Serial.print("Camera pronta! Acesse 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' para conectar");

}

void loop() {
  delay(10000);

}
