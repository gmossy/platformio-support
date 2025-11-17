#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Identification
// Adafruit SSD1306
// Screen Specifications
// this is a 0.91" or 0.96" I2C OLED display (most likely 0.96" given the aspect ratio).
// Resolution: 128x64 pixels (or 128x32 for 0.91")
// Interface: I2C (address typically 0x3C or 0x3D)
// Voltage: 3.3V - 5V compatible
// The Adafruit library is the easiest to start with and has excellent documentation. If you're memory-constrained, U8g2 or SSD1306Ascii are good alternatives.Retry
// Driver Chip
// SSD1306 - This is the most common driver IC for these 4-pin I2C OLED modules. The pin labels "GND VCC SCL SDA" confirm it's I2C.
// I2C OLED example: 4-pin module (VCC, GND, SDA, SCL)
// Connect to Arduino I2C pins:
//   - On Arduino Uno / Nano: SDA = A4, SCL = A5
//   - On many other boards: use dedicated SDA/SCL pins

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1      // Reset pin (or -1 if shared/unused)
#define OLED_I2C_ADDR 0x3C    // Common I2C address for 128x64 OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Simple monochrome bitmap icons (1-bit each pixel)
// 16x8 battery outline with a little terminal on the right
static const unsigned char PROGMEM batteryIcon[] = {
  0b00111111, 0b11111100,
  0b01100000, 0b00000110,
  0b01000000, 0b00000010,
  0b01000000, 0b00000010,
  0b01000000, 0b00000010,
  0b01000000, 0b00000010,
  0b01100000, 0b00000110,
  0b00111111, 0b11111100
};

// 16x12 Wi-Fi icon with three arcs and a small dot
static const unsigned char PROGMEM wifiIcon[] = {
  0b00000111, 0b11100000,
  0b00011111, 0b11111000,
  0b00111000, 0b00011100,
  0b01100000, 0b00000110,
  0b00000111, 0b11100000,
  0b00011111, 0b11111000,
  0b00111000, 0b00011100,
  0b00000001, 0b10000000,
  0b00000001, 0b10000000,
  0b00000000, 0b00000000,
  0b00000001, 0b10000000,
  0b00000001, 0b10000000
};

// 16x16 smiley face
static const unsigned char PROGMEM smileyIcon[] = {
  0b00000111, 0b11100000,
  0b00011111, 0b11111000,
  0b00111000, 0b00011100,
  0b01100000, 0b00000110,
  0b01000110, 0b01100010,
  0b10000110, 0b01100001,
  0b10000000, 0b00000001,
  0b10010000, 0b00001001,
  0b10001000, 0b00010001,
  0b10000111, 0b11100001,
  0b10000000, 0b00000001,
  0b01000000, 0b00000010,
  0b01100000, 0b00000110,
  0b00111000, 0b00011100,
  0b00011111, 0b11111000,
  0b00000111, 0b11100000
};

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

  // Draw status icons at the top: Wi-Fi (left), battery (right)
  display.drawBitmap(0, 0, wifiIcon, 16, 12, SSD1306_WHITE);
  display.drawBitmap(SCREEN_WIDTH - 16, 0, batteryIcon, 16, 8, SSD1306_WHITE);

  // Draw a smiley icon somewhere in the middle
  display.drawBitmap(0, 24, smileyIcon, 16, 16, SSD1306_WHITE);

  // Draw Hello, world! text to the right of the smiley
  display.setTextSize(2);           // Medium text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(24, 24);
  display.println("Hello,");
  display.println("world!");

  display.display();
}

void loop() {
  // Nothing to do in loop for a static Hello World message
}
