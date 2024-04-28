/*
 * ADC.c
 *
 * Created: 28.04.2024 02:13:30
 *  Author: Martin
 */ 

#include <avr/io.h>

#define ADC_STEP 4.3 / 255	// 4.3 volts / max adc value of 256

void adc_prepare(uint8_t adc_pin){
	PORTA.DIR &= ~adc_pin;
	PORTA.OUT &= ~adc_pin;
	ADC0.MUXPOS |= ADC_MUXPOS_AIN2_gc ;	// Connect PIN 2 to ADC
	VREF.CTRLA |= VREF_ADC0REFSEL_4V34_gc;	// Select 4.3V internal vref
	ADC0.CTRLA |= ADC_RESSEL_8BIT_gc | ADC_ENABLE_bm;	// Enable ADC with 8 bit resolution
	ADC0.CTRLC &= ~ADC_SAMPCAP_bm;	// Set reduced capacity for ADC input
}

uint8_t adc_get_reading(){
	ADC0.COMMAND |= ADC_STCONV_bm;	// start single conversion
	while( !ADC_RESRDY_bm );	// wait for new result
	uint8_t val = ADC0.RES;
	return val;
	//return (uint8_t) (ADC0.RES & 0x00FF);	// return result as 8bit
}

float adc_get_v_reading(){
	return adc_get_reading() * ADC_STEP;
}
