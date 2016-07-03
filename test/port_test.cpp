#include <Arduino.h>



void setup() {
  /* Setup PC13 as output */
  pinMode(PC13,OUTPUT);
}

void loop() {
  /* Using API function gpio_toggle(): */
  togglePin(PC13);
  for (int i = 0; i < 800000; i++)  /* Wait a bit. */
    __asm__("nop");
}
