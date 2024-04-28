/*
 * prescaler.c
 *
 * Created: 28.04.2024 16:43:04
 *  Author: Martin
 */ 

#include <avr/io.h>

void set_prescaler(CLKCTRL_PDIV_t prescaler){
	CCP |= CCP_IOREG_gc;	// remove configuration change protection for a second change
	CLKCTRL.MCLKCTRLB = prescaler | CLKCTRL_PEN_bm;	// change and enable prescaler
}