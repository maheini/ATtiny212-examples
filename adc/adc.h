/*
 * adc.h
 *
 * Created: 28.04.2024 17:52:44
 *  Author: Martin
 */ 


#ifndef ADC_H_
#define ADC_H_

/* Prepare ADC
 * Setup all registers in order to take measurements on the selected pin
 * Using 4.3V internal voltage reference
 */
void adc_prepare(uint8_t adc_pin);

/* ADC get reading
 * Start ADC and return it's value (max = 256)
 */
uint8_t adc_get_reading();

/* ADC get V reading
 * Start ADC conversion and return it's Volts value
 */
float adc_get_v_reading();

#endif /* ADC_H_ */