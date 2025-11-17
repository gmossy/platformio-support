#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// I2C OLED example: 4-pin module (VCC, GND, SDA, SCL)
// Connect to Arduino I2C pins:
//   - On Arduino Uno / Nano: SDA = A4, SCL = A5
//   - On many other boards: use dedicated SDA/SCL pins

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1      // Reset pin (or -1 if shared/unused)
#define OLED_I2C_ADDR 0x3C    // Common I2C address for 128x64 OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
    // If the display does not initialize, stay here
    for (;;) {
      // Optional: blink an onboard LED here to signal error
      delay(1000);
    }
  }

  display.clearDisplay();
  display.setTextSize(2);           // Medium text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello,");
  display.println("world!");
  display.display();
}

void loop() {
  // Nothing to do in loop for a static Hello World message
}
