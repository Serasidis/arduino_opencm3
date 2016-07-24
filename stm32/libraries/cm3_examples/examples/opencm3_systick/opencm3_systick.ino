volatile uint32_t mymillis;

void sys_tick_handler(void) {
    mymillis++;
}

void mydelay(uint32_t ms)
{
    uint32_t start = mymillis;
    while (mymillis - start < ms)
        ;
}

void setup() {
    /* Setup PC13 as output */
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

    mymillis = 0;
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);    /// SysTick at 72Mhz/8
    systick_set_reload(8999);                               /// SysTick Reload for 1ms tick
    systick_interrupt_enable();
    systick_counter_enable();
}

void loop() {
    gpio_clear(GPIOC,GPIO13);
    mydelay(50);
    gpio_set(GPIOC,GPIO13);
    mydelay(50);
}
