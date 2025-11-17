/*
 Blink 
  Arduino

This sketch Blinks a LED connected to Digital Pin 8 via a 330 Ohm resistors.
  Turns on for one second, then off for one second, repeatedly.
  
   This lesson introduces some of the most basic functions in the Arduino
   language: digitalWrite([pin], [HIGH/LOW]) and delay([milliseconds]).
   Used together, these functions can be used to control an LED and time!
   
   Written by Glenn Mossy, Mar 25, 2015
*/

void setup()   {                
  // Initialize Arduino Digital Pins 6-13 as outputs for multi-LED sequence
  for (int pin = 6; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop()                     
{
  // Fancy sequence on pins 6-13: forward chase, reverse chase, then all flash

  // Forward chase: light each LED from D6 to D13
  for (int pin = 6; pin <= 13; pin++) {
    digitalWrite(pin, HIGH);
    delay(120);
    digitalWrite(pin, LOW);
  }

  // Reverse chase: light each LED from D13 back to D6
  for (int pin = 13; pin >= 6; pin--) {
    digitalWrite(pin, HIGH);
    delay(120);
    digitalWrite(pin, LOW);
  }

  // All LEDs flash twice together
  for (int i = 0; i < 2; i++) {
    for (int pin = 6; pin <= 13; pin++) {
      digitalWrite(pin, HIGH);
    }
    delay(200);
    for (int pin = 6; pin <= 13; pin++) {
      digitalWrite(pin, LOW);
    }
    delay(200);
  }
}
