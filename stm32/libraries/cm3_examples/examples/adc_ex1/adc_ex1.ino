/*
  Simple ADC reading 
*/

void setup() {
  Serial.begin(115200);
  Serial.println("---START---");
  Serial.println("---INIT---");
}


void loop() {

  int start = micros();
  uint32_t sensorValue = analogRead(A0);
  unsigned long end = micros();
  Serial.print(end - start);
  Serial.print("uS. Value :");
  Serial.print(sensorValue);
  Serial.println("");
  delay(100);
}
