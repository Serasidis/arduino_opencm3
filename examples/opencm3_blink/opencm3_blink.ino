
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>


void setup() {
    rcc_clock_setup_in_hse_8mhz_out_72mhz();    /// Clock 72Hz from HSE 8MHz
    /* Enable GPIOC clock. */
    rcc_periph_clock_enable(RCC_GPIOC);
    /* Set GPIO13 (in GPIO port C) to 'output push-pull'. */
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
}

void loop() {
    /* Using API function gpio_toggle(): */
    gpio_toggle(GPIOC, GPIO13); /* LED on/off */
    for (int i = 0; i < 800000; i++)  /* Wait a bit. */
      __asm__("nop");
}
