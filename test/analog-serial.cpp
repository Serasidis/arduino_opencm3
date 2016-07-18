#include <Arduino.h>
#include <stm32/gpio_arch.h>
#include <stm32/adc_arch.h>

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
  Serial.print(" Vref :");
  Serial.print(adc_getVref());
  Serial.print(" Temp :");
  Serial.print(adc_getTemperature());
  Serial.println("");
  delay(100);
}
