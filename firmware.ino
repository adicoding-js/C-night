#include "esp_camera.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 therm = Adafruit_MLX90614();
Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 13, 11, 12, 14);

int laser = 0;
int ir= 0;
  int hud_color_index = 0;
uint16_t hudcolors[3] = {ILI9341_RED, ILI9341_GREEN, ILI9341_WHITE};

unsigned long lastDebounce = 0;

void setup() {
  Serial.begin(115200);
pinMode(1, OUTPUT); // laser_control
pinMode(2, OUTPUT); // ir_led_control
pinMode(42, OUTPUT); // buzzer
pinMode(21, OUTPUT); // tft_blk

pinMode(4, INPUT_PULLUP); // shutter
pinMode(5, INPUT_PULLUP); // ir btn
pinMode(6, INPUT_PULLUP); // hud btn
pinMode(7, INPUT_PULLUP); // laser btn

digitalWrite(1, LOW);
digitalWrite(2, LOW);
digitalWrite(21, HIGH);

tft.begin();
tft.setRotation(1);
tft.fillScreen(ILI9341_BLACK);

  Wire.begin(8, 9);
  if (!therm.begin()) {
Serial.println("mlx problem");
  }

camera_config_t config;
config.ledc_channel = LEDC_CHANNEL_0;
config.ledc_timer = LEDC_TIMER_0;
config.pin_d0 = 38;
config.pin_d1 = 39;
config.pin_d2 = 40;
config.pin_d3 = 41;
config.pin_d4 = 47;
config.pin_d5 = 48;
config.pin_d6 = 33;
config.pin_d7 = 34;
config.pin_xclk = 15;
config.pin_pclk = 16;
config.pin_vsync = 17;
config.pin_href = 18;
config.pin_sccb_sda = 8;
config.pin_sccb_scl = 9;
config.pin_pwdn = -1;
config.pin_reset = -1;
config.xclk_freq_hz = 20000000;
config.pixel_format = PIXFORMAT_RGB565;
config.frame_size = FRAMESIZE_QVGA;
config.jpeg_quality = 12;
config.fb_count = 1;

  if (psramFound()) {
config.fb_count = 2;
  }

  esp_err_t err = esp_camera_init(&config);
if (err != ESP_OK) {
    Serial.printf("cam init failed 0x%x", err);
  }
}

void loop() {

if (millis() - lastDebounce > 250) {
    if (digitalRead(7) == LOW) { 
  laser = !laser;
      digitalWrite(1, laser ? HIGH : LOW);
    lastDebounce = millis();
}
if (digitalRead(5) == LOW) { 
      ir = !ir;
  digitalWrite(2, ir ? HIGH : LOW);
    lastDebounce = millis();
    }

if (digitalRead(6) == LOW) { 
hud_color_index = hud_color_index + 1;
      if (hud_color_index > 2) {
    hud_color_index = 0;
}
  lastDebounce = millis();
    }

    if (digitalRead(4) == LOW) { 
  digitalWrite(42, HIGH);
      delay(100);
digitalWrite(42, LOW);
    lastDebounce = millis();
    }
  }
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
Serial.println("cam capture failed");
    return;
  }
  tft.drawRGBBitmap(0, 0, (uint16_t *)fb->buf, 320, 240);
  esp_camera_fb_return(fb);

float objTemp = therm.readObjectTempC();
uint16_t activeColor = hudcolors[hud_color_index];

tft.drawCircle(160, 120, 15, activeColor);
tft.drawLine(160, 100, 160, 140, activeColor);
tft.drawLine(140, 120, 180, 120, activeColor);

tft.setCursor(10, 10);
tft.setTextSize(3);
tft.setTextColor(activeColor);
tft.print("TEMP: ");
tft.print(objTemp, 1);
  tft.print(" C");

tft.setTextSize(2);
tft.setCursor(10, 210);
  if (laser) {
tft.print("[LASER] ");
  }
if (ir) {
    tft.print("[NIGHT_VISION]");
  }
}