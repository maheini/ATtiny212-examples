/*
 * ATtiny212.c
 *
 * Created: 17.04.2024 21:13:22
 * Author : Martin
 */ 

#include <avr/io.h>
#define F_CPU 10000000
#include <util/delay.h>

#include "../blinkcode.h"
#include "../pwm/pwm.h"
#include "../prescaler/prescaler.h"
#include "../adc/adc.h"
#include "../pin_listen/pin_listen.h"

#define ADC_PIN PIN2_bm
#define LED_PIN PIN1_bm

int state = 0;

void switch_direction (){
	state = state ? 0 : 1;
	while(PORTA.IN & PIN1_bm);
	_delay_ms(10);
	while(!(PORTA.IN & PIN1_bm));
}

int dimmer_on_steroids(void){
	set_prescaler(CLKCTRL_PDIV_10X_gc);
	
	listen_pin(PIN1_bm, switch_direction);
	
	pwm_start(100, 0);
	
	pwm_start(100, 0);
	
	adc_prepare(PIN2_bm);
	
	float stepcount = 100 / 4.3;
	int prev_val = 0;
	
	int max_step = 1;
	int step_adjust = 50;
	int step_counter = 0;
	
	int oldstate = 0;
	int state_change = 0;
	
	while(1){
		float reading = adc_get_v_reading(); 
		int setting = 0;
		
		if(state){
			setting = reading * stepcount;
		} else {
			setting = 100 - reading * stepcount;
		}
		
		// Check if state has changed
		if (state != oldstate){
			oldstate = state;
			state_change = 1;
			step_counter = 0;
		}
		
		// smooth state change
		if(state_change){
			if(step_counter >= step_adjust){
				step_counter = 0;
				// too big step upwards? limit step to max_step
				if (setting > (prev_val + max_step)){
					setting = prev_val + max_step;
				}
				// too small step downwards? limit step to max_step
				else if (setting < (prev_val - max_step)){
					setting = prev_val - max_step;
				}
				// step within limit? stop state_change
				else {
					state_change = 0;
				}
			} else {
				setting = prev_val;
			}
			step_counter ++;
		}
		pwm_adjust(setting);
		
		prev_val = setting;
	}
}

