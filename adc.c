/*
 * ADC.c
 *
 * Created: 28.04.2024 02:13:30
 *  Author: Martin
 */ 


#include <avr/io.h>

void prepare(uint8_t input_pin){
	PORTA.DIR &= ~input_pin;
	PORTA.OUT &= ~input_pin;
	ADC0.MUXPOS |= ADC_MUXPOS_AIN2_gc ;	// Connect PIN 2 to ADC
	VREF.CTRLA |= VREF_ADC0REFSEL_2V5_gc;	// Select 4.3V internal vref
	ADC0.CTRLA |= ADC_RESSEL_8BIT_gc | ADC_ENABLE_bm;	// Enable ADC with 8 bit resolution
	ADC0.CTRLC &= ~ADC_SAMPCAP_bm;	// Set reduced capacity for ADC input
}

uint16_t start_conversion(){
	ADC0.COMMAND |= ADC_STCONV_bm;	// start single conversion
	while( !ADC_RESRDY_bm );	// wait for new result
	return ADC0.RES;	// return result
}