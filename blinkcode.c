/*
 * blinkcode.c
 *
 * Created: 28.04.2024 02:13:30
 *  Author: Martin
 */ 

#include <avr/io.h>
#include <util/delay.h>

void await(int ms){
	while (ms-- != 0)
	_delay_ms(1);
}

void blink_now(uint8_t led_pin, double duration_ms){
	PORTA.DIR |= led_pin;	// Set led_pin as output
	
	while(1){
		
		await(duration_ms);
		PORTA.OUT ^= led_pin;
	}
	return;
}
