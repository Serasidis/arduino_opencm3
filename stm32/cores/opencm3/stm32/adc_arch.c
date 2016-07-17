#include "adc_arch.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>


void adc_init()
{
    int i;
    rcc_periph_clock_enable(RCC_ADC1);
    /* Make sure the ADC doesn't run during config. */
	adc_power_off(ADC1);
    /* We configure everything for one single conversion. */
	adc_disable_scan_mode(ADC1);
	adc_set_single_conversion_mode(ADC1);
	adc_disable_external_trigger_regular(ADC1);
	adc_set_right_aligned(ADC1);
#ifdef STM32F1
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_28DOT5CYC);
#elif defined STM32F4
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_3CYC);
#endif
    adc_power_on(ADC1);
    	/* Wait for ADC starting up. */
	for (i = 0; i < 800000; i++)    /* Wait a bit. */
		__asm__("nop");
  /* Enable ADC<X> */
#if defined(STM32F1)
  /* Enable ADC<X> reset calibaration register */
  adc_reset_calibration(ADC1);
  /* Check the end of ADC<X> reset calibration */
  while ((ADC_CR2(ADC1) & ADC_CR2_RSTCAL) != 0);
  /* Start ADC<X> calibaration */
  adc_calibration(ADC1);
  /* Check the end of ADC<X> calibration */
  while ((ADC_CR2(ADC1) & ADC_CR2_CAL) != 0);
#endif
}
