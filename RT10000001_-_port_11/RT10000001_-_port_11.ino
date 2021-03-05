#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   2
#define OLED_CLK   0
#define OLED_DC    5
#define OLED_CS    17
#define OLED_RESET 4

const int vccPin = 23;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

String palavra;

void setup() {
  digitalWrite(vccPin, HIGH);
  // Abaixo tudo igual ao exercício 11 de arduino.
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("ready!"));
  display.display();      // Show initial text
  delay(100);
}

void loop() {
  while (Serial.available() > 0);
  palavra = Serial.readStringUntil('\n');
  if (palavra == "oled hello") {
    display.clearDisplay();
    display.setTextSize(1);
    display.println(F("hello world"));
    display.display();
  }
  if (palavra == "oled clear") {
    display.clearDisplay();
    display.display();
  }
}
