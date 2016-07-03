#include <Arduino.h>

void setup() {
  /* Setup PC13 as output */
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
}

void loop() {
  /* Using API function gpio_toggle(): */
  gpio_toggle(GPIOC, GPIO13); /* LED on/off */
  delay(50);
}
