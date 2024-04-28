/*
 * pwm.h
 *
 * Created: 28.04.2024 15:46:54
 *  Author: Martin
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

/* pwm start
 * Start single-slope PWM generator on PIN3
 * 
 * period = max counter value per cycle
 * duration = max pulse duration (within period)
 */
void pwm_start(uint16_t period, uint16_t duration);

/* pwm adjust
 * Adjust PWM duration of a running PWM
 */
void pwm_adjust(uint16_t duration);

#endif /* INCFILE1_H_ */