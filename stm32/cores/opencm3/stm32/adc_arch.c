/*
  Copyright (C)2016 Evangelos Arkalis

  This file is part of arduino_opencm3.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>

#include "adc_arch.h"
#include "gpio_arch.h"
#include "sys_arch.h"

/*
    Select adcpre

*/

void adc_setPrescale(uint32_t apb2)
{
    uint32_t adcpre;
#ifdef STM32F1
    if (apb2<28000000) {
        adcpre = RCC_CFGR_ADCPRE_PCLK2_DIV2;
    } else if (apb2<56000000) {
        adcpre = RCC_CFGR_ADCPRE_PCLK2_DIV4;
    } else if (apb2<84000000) {
        adcpre = RCC_CFGR_ADCPRE_PCLK2_DIV6;
    } else {
        adcpre = RCC_CFGR_ADCPRE_PCLK2_DIV8;
    }
    rcc_set_adcpre(adcpre);
#elif defined STM32F4
    if (apb2<28000000) {
        adcpre = ADC_CCR_ADCPRE_BY2;
    } else if (apb2<56000000) {
        adcpre = ADC_CCR_ADCPRE_BY4;
    } else if (apb2<84000000) {
        adcpre = ADC_CCR_ADCPRE_BY6;
    } else {
        adcpre = ADC_CCR_ADCPRE_BY8;
    }
    adc_set_clk_prescale(adcpre);
#endif


}


void adc_init()
{
    rcc_periph_clock_enable(RCC_ADC1);
	adc_power_off(ADC1);
#ifdef STM32F1
    rcc_periph_reset_pulse(RST_ADC1);
#elif defined STM32F4
#endif
    adc_setPrescale(rcc_apb2_frequency);
#ifdef STM32F1
    adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
#elif defined STM32F4
#endif
    adc_disable_scan_mode(ADC1);
    adc_set_single_conversion_mode(ADC1);
    adc_disable_external_trigger_regular(ADC1);
	adc_set_right_aligned(ADC1);
#ifdef STM32F1
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_13DOT5CYC);
    adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_SWSTART);
#elif defined STM32F4
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_3CYC);
#endif
    adc_power_on(ADC1);
    delay_nano(5000);
#if defined(STM32F1)
    adc_reset_calibration(ADC1);
    adc_calibration(ADC1);
#endif
}

uint32_t adc_read()
{
	adc_start_conversion_regular(ADC1);
	while (!adc_eoc(ADC1));
	uint16_t valueRead = adc_read_regular(ADC1);
}

float adc_getTemperature()
{
    adc_init();
// --- Again API differencies
#ifdef STM32F1
    adc_enable_temperature_sensor(ADC1);
#elif defined STM32F4
    adc_enable_temperature_sensor();
#endif // STM32F1
    delay_nano(1500);
// --- Again API differencies
#ifdef STM32F1
    uint8_t channel = ADC_CHANNEL_TEMP;
#elif defined STM32F4
    uint8_t channel = ADC_CHANNEL_TEMP_F40;
#endif // STM32F1
	adc_set_regular_sequence(ADC1, 1, &channel);
    uint32_t valueRead = adc_read();
	adc_power_off(ADC1);

	// TODO floating point calculations

	return (float)valueRead;
}

float adc_getVref()
{
    adc_init();
// --- Again API differencies
#ifdef STM32F1
    adc_enable_temperature_sensor(ADC1);
#elif defined STM32F4
    adc_enable_temperature_sensor();
#endif // STM32F1
    delay_nano(1500);
    uint8_t channel = ADC_CHANNEL_VREF;
	adc_set_regular_sequence(ADC1, 1, &channel);
    uint32_t valueRead = adc_read();
	adc_power_off(ADC1);

	// TODO floating point calculations

	return (float)valueRead;
}
