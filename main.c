/*
 * ATtiny212.c
 *
 * Created: 17.04.2024 21:13:22
 * Author : Martin
 */ 

#include <avr/io.h>
#define F_CPU 10000000
#include <util/delay.h>

#include "blinkcode.h"
#include "pwm/pwm.h"
#include "prescaler/prescaler.h"
#include "adc/adc.h"

#define ADC_PIN PIN2_bm
#define LED_PIN PIN1_bm

float get_dd(){
	return 5.2;
}

int main(void){
	set_prescaler(CLKCTRL_PDIV_10X_gc);
	pwm_start(100, 0);
	
	adc_prepare(PIN2_bm);
	
	float stepcount = 100 / 4.3;
	
	while(1){
		pwm_adjust(adc_get_v_reading() * stepcount);
	}
	
	int counter = 50;
	int upwards = 1;
	while(1){
		pwm_adjust(counter);
		
		if (counter >= 100){
			upwards = 0;
		} else if (counter <= 50){
			upwards = 1;
		}
		counter = upwards ? counter + 1 : counter - 1;
		
		_delay_ms(200);
	}
}

