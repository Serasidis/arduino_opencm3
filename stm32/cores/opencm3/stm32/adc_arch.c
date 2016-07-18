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

#include "adc_arch.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>

/*
    Select adcpre

*/

void adc_setPrescale(uint32_t apb2)
{
    uint32_t adcpre;
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
}


void adc_init()
{
    int i;
    rcc_periph_clock_enable(RCC_ADC1);
	adc_power_off(ADC1);
    rcc_periph_reset_pulse(RST_ADC1);
    adc_setPrescale(rcc_apb2_frequency);
    adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
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
#if defined(STM32F1)
    adc_reset_calibration(ADC1);
    adc_calibration(ADC1);
#endif
}

uint32_t adc_read()
{
#ifdef STM32F1
	adc_start_conversion_direct(ADC1);
#elif defined STM32F4
	adc_start_conversion_regular(ADC1);
#endif
	while (!adc_eoc(ADC1));
	uint16_t valueRead = adc_read_regular(ADC1);
}

float getTemperature()
{
    int i;
    adc_init();
#ifdef STM32F1
    adc_enable_temperature_sensor(ADC1);
#elif defined STM32F4
    adc_enable_temperature_sensor();
#endif // STM32F1
	//for (i = 0; i < 1000; i++)    /* Wait a bit. */
	//	__asm__("nop");
    //uint8_t channel_array[1];
    //channel_array[0]=16;
	//adc_set_regular_sequence(ADC1, 1, channel_array);
	//uint32_t ts = adc_read();
    //channel_array[0]=17;
	//adc_set_regular_sequence(ADC1, 1, channel_array);
	//uint32_t vref = adc_read();
	//adc_power_off(ADC1);

	uint32_t ts = 0;
	uint32_t vref = 1;

	    /* Datasheet 3.15.1 */
    uint32_t ts_cal1  = *((uint16_t*)0x1fff75a8);
    uint32_t ts_cal2  = *((uint16_t*)0x1fff75ca);

    /* Datasheet 3.15.2 */
    uint32_t vrefint = *((uint16_t*)0x1fff75aa);

    /* Compensate TS_DATA for VDDA vs. 3.0 */
     ts = (ts * vrefint) / vref;

    return (30.0 + ((float)(110.0 - 30.0) * (float)(ts - ts_cal1)) / (float)(ts_cal2 - ts_cal1));
}
