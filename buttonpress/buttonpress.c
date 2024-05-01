/*
 * buttonpress.c
 *
 * Created: 01.05.2024 22:23:24
 *  Author: Martin
 */ 

#include <avr/interrupt.h>
typedef void (*callback_fcn)();

volatile callback_fcn registered_callback[8];

void listen_pin(uint8_t pin, void (*callback)()){
	uint8_t pinctrl_cfg = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
	PORTA.DIR &= ~pin;
	
