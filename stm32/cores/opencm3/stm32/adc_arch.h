#ifndef ADC_ARCH_H_INCLUDED
#define ADC_ARCH_H_INCLUDED

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>

BEGIN_DECLS

void adc_setPrescale(uint32_t apb2);
void adc_init(void);
uint32_t adc_read(void);

END_DECLS

#endif // ADC_ARCH_H_INCLUDED
