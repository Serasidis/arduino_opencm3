#include <Arduino.h>
#include <stm32/gpio_arch.h>
#include <stm32/adc_arch.h>

float a,b;

float getVref()
{
    int i;
    adc_init();
#ifdef STM32F1
    adc_enable_temperature_sensor(ADC1);
#elif defined STM32F4
    adc_enable_temperature_sensor();
#endif // STM32F1
	for (i = 0; i < 1000; i++)    /* Wait a bit. */
		__asm__("nop");
    uint8_t channel_array;
    channel_array=17;
	adc_set_regular_sequence(ADC1, 1, &channel_array);
	uint32_t vref = adc_read();
	vref = adc_read();
	adc_power_off(ADC1);
    Serial.print(" VREF:");
	Serial.print(vref);
	Serial.print("] ");
	return (float)(1200*4096)/(float)vref;
}


float getTemperature2()
{
    int i;
    adc_init();
#ifdef STM32F1
    adc_enable_temperature_sensor(ADC1);
#elif defined STM32F4
    adc_enable_temperature_sensor();
#endif // STM32F1
	for (i = 0; i < 1000; i++)    /* Wait a bit. */
		__asm__("nop");
    uint8_t channel_array;
    channel_array=16;
	adc_set_regular_sequence(ADC1, 1, &channel_array);
	uint32_t ts = adc_read();
	ts = adc_read();
	adc_power_off(ADC1);

	Serial.print("[ TS:");
	Serial.print(ts);
	Serial.print("] ");
    return (float)ts;
}

void setup() {
  Serial.begin(115200);
  Serial.println("---START---");
  Serial.println("---INIT---");
}


void loop() {

  int start = micros();
  int sensorValue = analogRead(A0);
  unsigned long end = micros();
  Serial.print(end - start);
  Serial.print("uS. Value :");
  Serial.print(sensorValue);
  Serial.print(" Temperature:");
  Serial.println(getVref());
  Serial.println(getTemperature2());
  delay(100);
}
