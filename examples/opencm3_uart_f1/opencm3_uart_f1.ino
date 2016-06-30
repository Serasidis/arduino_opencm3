int i, j = 0, c = 0;

void setup() {
  /* Set GPIO13 (in GPIO port C) to 'output push-pull'. */
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

  /* Setup GPIO pin GPIO_USART1_TX. */
  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

  /* Enable clocks for USART1. */
  rcc_periph_clock_enable(RCC_USART1);

  /* Setup UART parameters. */
  usart_set_baudrate(USART1, 115200);
  usart_set_databits(USART1, 8);
  usart_set_stopbits(USART1, USART_STOPBITS_1);
  usart_set_mode(USART1, USART_MODE_TX);
  usart_set_parity(USART1, USART_PARITY_NONE);
  usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

  /* Finally enable the USART. */
  usart_enable(USART1);

}

void loop() {
    /* Using API function gpio_toggle(): */
    gpio_toggle(GPIOC, GPIO13); /* LED on/off */
    usart_send_blocking(USART1, c + '0'); /* USART1: Send byte. */
    c = (c == 9) ? 0 : c + 1; /* Increment c. */
    if ((j++ % 80) == 0) {  /* Newline after line full. */
      usart_send_blocking(USART1, '\r');
      usart_send_blocking(USART1, '\n');
    } 
    for (int i = 0; i < 800000; i++)  /* Wait a bit. */
      __asm__("nop");
}
