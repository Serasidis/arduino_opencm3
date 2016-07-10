#include <Arduino.h>

void setup() {
  pinMode(LED1,OUTPUT);
}

void loop() {
  /* Using API function gpio_toggle(): */
  togglePin(LED1);
  delay(100);
}
