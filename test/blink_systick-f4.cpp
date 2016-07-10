#include <Arduino.h>

void setup() {
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
}

void loop() {
  /* Using API function gpio_toggle(): */
  gpio_toggle(GPIOA, GPIO5); /* LED on/off */
  delay(500);
}
