/*
 * ATtiny212.c
 *
 * Created: 17.04.2024 21:13:22
 * Author : Martin
 */ 

#define F_CPU 2000000	// Set clock at 2MHZ

#include <avr/io.h>

#include "blinkcode.h"


#define ADC_PIN PIN2_bm
#define LED_PIN PIN1_bm

int main(void){
	set_prescaler(CLKCTRL_PDIV_2X_gc);
	blink_now(LED_PIN, 1000);
}