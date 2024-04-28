/*
 * ATtiny212.c
 *
 * Created: 17.04.2024 21:13:22
 * Author : Martin
 */ 

#define F_CPU 2000000	// Set clock at 2MHZ

#include <avr/io.h>
#include <avr/delay.h>

#define ADC_PIN PIN2_bm
#define LED_PIN PIN1_bm

int main(void){
	PORTA.DIR |= LED_PIN;	// Set PIN 1 as output
	
	CCP |= CCP_IOREG_gc;	// remove configuration change protection for a second change
	CLKCTRL.MCLKCTRLB = CLKCTRL_PDIV_10X_gc | CLKCTRL_PEN_bm;	// change and enable prescaler
	
	CLKCTRL.MCLKCTRLA |= CLKCTRL_CLKOUT_bm;	// Output clock signal
	
	
	while(1){
		_delay_ms(1000);
		PORTA.OUT ^= LED_PIN;
	}
}


void converter(){
	PORTA.DIR &= ~ADC_PIN;
	PORTA.OUT &= ~ADC_PIN;
	
	ADC0.MUXPOS |= ADC_MUXPOS_AIN2_gc ;	// Connect PIN 2 to ADC
	VREF.CTRLA |= VREF_ADC0REFSEL_2V5_gc;	// Select 4.3V internal vref
	ADC0.CTRLA |= ADC_RESSEL_8BIT_gc | ADC_ENABLE_bm;	// Enable ADC with 8 bit resolution
	ADC0.CTRLC &= ~ADC_SAMPCAP_bm;	// Set reduced capacity for ADC input
	
	while(1){
		ADC0.COMMAND |= ADC_STCONV_bm;	// start single conversion
		while( !ADC_RESRDY_bm );	// wait for new result
		uint16_t result = ADC0.RES;	// get result
		int level = 0.09803921568627450980392156862745 * result;
		//if (level > 12){
		if( result > 254 ){
			PORTA.OUT |= LED_PIN;
			} else {
			PORTA.OUT &= ~LED_PIN;
		}
	}
}
