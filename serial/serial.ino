void setup() {
  Serial.begin(9600);
}

int value = 10;
void loop() {
    Serial.print(value);
    Serial.print("\n");

    value++;
}
