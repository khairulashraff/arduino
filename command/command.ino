// include the library code:
#include <LiquidCrystal.h>'

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  while (Serial.available()) {
    int b = Serial.read();

    lcd.setCursor(0, 0);
    lcd.print(b);
    lcd.print("                         ");
    Serial.println(b); 
  }
}
