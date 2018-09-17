/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>'

const int CMD_ID = 5;

const int P_LDR = A0;
const int P_LDR_LED = 13;
const int LDR_DAYLIGHT_THRESHOLD = 300;

int CONFIG_LDR_AUTO = 1;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("Setting up..");

  // Setup LDR
  pinMode(P_LDR, INPUT);

  // Setup LED indicator
  pinMode(P_LDR_LED, OUTPUT);

  // use serial for commands
  Serial.begin(9600);

  // Just because
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Ready!               ");
}

void loop() {
  readCommand();
  
//  int ldrStatus = analogRead(P_LDR);
//  
//  // set the cursor to column 0, line 1
//  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
//  lcd.print(ldrStatus);
//
//  lcd.setCursor(0, 0);
//
//  if (CONFIG_LDR_AUTO) {
//    if (ldrStatus < LDR_DAYLIGHT_THRESHOLD) {
//      lcd.print(F("Night!"));
//      digitalWrite(P_LDR_LED, HIGH);
//    }
//    else {
//      lcd.print(F("Day!              "));
//      digitalWrite(P_LDR_LED, LOW);
//    }
//  }
}

int read_mode = 0;
int read_index = 0;
int read_length = 0;
int read_buffer[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void readCommand() {
  if (read_mode) {
    return;
  }
  
  while (Serial.available()) {
    int b = Serial.read();
    
    // Don't ask why
    delay(20);

    read_mode = 1;
    read_buffer[read_index++] = b;

//    if (read_mode) {
//      read_buffer[read_index] = b;
//      read_index++;
//    }
//    else {
//      int id = b >> 4;
//      
//      if (id == CMD_ID) {
//        read_mode = 1;
//        read_length = b & 0x0F;
//      }
//    }
  }

  if (read_buffer[0] == 0) {
    return;
  }
  
  int id = read_buffer[0] >> 4;
  if (id != CMD_ID) {
    read_mode = 0;
    return;
  }

  read_length = read_buffer[0] & 0x0F;

  // Length add by 1 to account for first byte 
  if (read_index == read_length+1) {
    lcd.setCursor(0, 0);
    lcd.print(F("Command received"));

    lcd.setCursor(0, 1);
    lcd.print(read_buffer[0]);
    lcd.print(F("-"));
    lcd.print(read_buffer[1]);
    lcd.print(F("-"));
    lcd.print(read_buffer[2]);
    lcd.print(F("-"));
    lcd.print(read_buffer[3]);
    lcd.print(F("                    "));

    delay(2000);
    executeCommand();
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print(F("Invalid command"));
    
    lcd.setCursor(0, 1);
    lcd.print(F("EXP: "));
    lcd.print(read_length);
    lcd.print(F(" LEN: "));
    lcd.print(read_index);
  }

  // Reset read mode
  read_index = 0;
  read_mode = 0;
  read_length = 0;
}

const int CMD_TYPE_LCD = 1;
const int CMD_TYPE_LDR = 2;
const int CMD_TYPE_LIGHT = 3;

void executeCommand() {
  lcd.setCursor(0, 0);
  lcd.print(F("Executing..                  "));

  switch (read_buffer[1]) {
    case CMD_TYPE_LCD:
      commandLcd();
      break; 
      
    case CMD_TYPE_LDR:
      commandLdr();
      break; 
      
    case CMD_TYPE_LIGHT:
      commandLight();
      break; 
  }

  // Clear command
  for (int i=0; i<sizeof(read_buffer);i++) {
    read_buffer[i] = 0x00;
  }
}

void commandLcd() {
  lcd.setCursor(0, 1);
  lcd.print("LCD..              ");
}

void commandLdr() {
  lcd.setCursor(0, 1);
  lcd.print("LDR..              ");
}

void commandLight() {
  lcd.setCursor(0, 1);
  lcd.print("Light..              ");
}
