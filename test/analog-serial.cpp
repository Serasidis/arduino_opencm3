#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("---START---");
}


void loop() {
  int start = micros();
  int sensorValue = analogRead(A0);
  unsigned long end = micros();
  Serial.print(end - start);
  Serial.print("uS. Value :");
  Serial.println(sensorValue);

}
