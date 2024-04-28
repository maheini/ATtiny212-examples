/*
 * pwm.c
 *
 * Created: 28.04.2024 15:46:47
 *  Author: Martin
 */ 

#include <avr/io.h>

void pwm_start(uint16_t period, uint16_t duration){
	TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm |TCA_SINGLE_WGMODE_SINGLESLOPE_gc;	// enable singleslope pwm generation
	TCA0.SINGLE.PERBUF = period;
	TCA0.SINGLE.CMP0BUF = duration;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc	| TCA_SINGLE_ENABLE_bm; // CLK_PER divider by 256 & enable
	PORTA.DIR |= PIN3_bm;	// Set pwm port as output
}

void pwm_adjust(uint16_t duration){
	TCA0.SINGLE.CMP0BUF = duration;
}