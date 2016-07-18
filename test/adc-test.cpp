#include <Arduino.h>
#include <stm32/adc_arch.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/cm3/dwt.h>

void setup() {
  Serial.begin(115200);
  Serial.println("---START---");
  dwt_enable_cycle_counter();
}

void loop() {

  int start = micros();


    rcc_periph_clock_enable(RCC_ADC1);
    adc_power_off(ADC1);
    rcc_periph_reset_pulse(RST_ADC1);
    adc_setPrescale(rcc_apb2_frequency);

    adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
    adc_disable_scan_mode(ADC1);
    adc_set_single_conversion_mode(ADC1);
    adc_disable_external_trigger_regular(ADC1);
	adc_set_right_aligned(ADC1);
    //adc_set_sample_time(ADC1, ADC_CHANNEL_VREF, ADC_SMPR_SMP_13DOT5CYC);
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_13DOT5CYC);
    adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_SWSTART);
    adc_power_on(ADC1);
    adc_enable_temperature_sensor(ADC1);
    adc_reset_calibration(ADC1);
    adc_calibration(ADC1);
    uint8_t channel = ADC_CHANNEL_VREF;
	adc_set_regular_sequence(ADC1, 1, &channel);
    adc_start_conversion_regular(ADC1);
    while (! adc_eoc(ADC1));
    uint32_t v = adc_read_regular(ADC1);

  unsigned long end = micros();
  Serial.print(end - start);
  Serial.print("uS >");
  Serial.print(v);
  Serial.print(" > ");
  Serial.print( rcc_ahb_frequency );
  Serial.println("");
  delay(100);
}
