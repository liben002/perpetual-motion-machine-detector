// This program interacts with the perpetual motion machine detector to provide detection capabilities.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);

String init_message = "Initializing...";
String base_message_top = "Press scan";
String base_message_bottom = "to detect.";
String scan_message = "Scanning...";
String result_message_top = "Not a perpetual";
String result_message_bottom = "motion machine.";

// 0 for base, 1 for scanning, 2 for result
int stage;

const int scan_button_pin = 2;
int scan_button_state;
bool scan_ready;

// piezo buzzer
const int tone_freq = 440;
const int buzzer_pin = 8;

void setup() {
  // put your setup code here, to run once:
  lcd.init();

  lcd.backlight();
  lcd.print("Initializing...");

  stage = 0;

  // setup buzzer
  pinMode(buzzer_pin, OUTPUT);
  
  // setup scan button
  pinMode(scan_button_pin, INPUT);
  scan_button_state = 0;
  scan_ready = true;

  delay(1000);

  lcd.clear();
  lcd.print(base_message_top);
  lcd.setCursor(0,1);
  lcd.print(base_message_bottom);
}

void loop() {
  lcd.clear();
  
  while(digitalRead(scan_button_pin) != HIGH) {
    lcd.setCursor(0,0);
    lcd.print(base_message_top);
    lcd.setCursor(0,1);
    lcd.print(base_message_bottom);
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(scan_message);
  beep(tone_freq, 200);
  beep(tone_freq, 200);
  beep(tone_freq, 1000);
  stage = 2;

  lcd.setCursor(0,0);
  lcd.print(result_message_top);
  lcd.setCursor(0,1);
  lcd.print(result_message_bottom);

  delay(5000);

  
//  scan_button_state = digitalRead(scan_button_pin);
//  // put your main code here, to run repeatedly:
//  if (stage == 0) {
//    lcd.setCursor(0,0);
//    lcd.print(base_message_top);
//    lcd.setCursor(0,1);
//    lcd.print(base_message_bottom);
//  } else if (stage == 1) {
//    lcd.setCursor(0,0);
//    lcd.print(scan_message);
//    beep(tone_freq, 200);
//    beep(tone_freq, 200);
//    beep(tone_freq, 1000);
//    stage = 2;
//  } else {
//    lcd.setCursor(0,0);
//    lcd.print(result_message_top);
//    lcd.setCursor(0,1);
//    lcd.print(result_message_bottom);
//    scan_ready = true;
//    stage = 0;
//    delay(5000);
//  }
//
//  if (scan_button_state == HIGH && scan_ready) {
//    stage = 1;
//    scan_ready = false;
//  }
}

void beep(int note, int duration) {
  // play tone on buzzer_pin
  tone(buzzer_pin, 440, duration);
  delay(duration);
  noTone(buzzer_pin);
}
