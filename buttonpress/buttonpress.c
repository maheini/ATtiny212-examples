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
	
	switch(pin){
		case PIN0_bm:
			PORTA_PIN0CTRL = pinctrl_cfg;
			registered_callback[0] = callback;
			break;
		case PIN1_bm:
			PORTA_PIN1CTRL = pinctrl_cfg;
			registered_callback[1] = callback;
			break;
		case PIN2_bm:
			PORTA_PIN2CTRL = pinctrl_cfg;
			registered_callback[2] = callback;
			break;
		case PIN3_bm:
			PORTA_PIN3CTRL = pinctrl_cfg;
			registered_callback[3] = callback;
			break;
		case PIN6_bm:
			PORTA_PIN6CTRL = pinctrl_cfg;
			registered_callback[6] = callback;
			break;
		case PIN7_bm:
			PORTA_PIN7CTRL = pinctrl_cfg;
			registered_callback[7] = callback;
			break;
	}
	sei();
}
