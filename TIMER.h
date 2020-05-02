/*
 * TIMER.h
 *
 *  Created on: Apr 14, 2020
 *      Author: DELL
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"


typedef enum {GPTM_OFF,GPTM_ON} timer_status_t;
typedef enum {TIMERA,TIMERB,CONCATENATED} timer_wide_t;
typedef enum {TIMER0,TIMER1,TIMER2,TIMER3,TIMER4,TIMER5} timer_id_t;
typedef enum {ONE_SHOT,PERIODIC,RTC,EDGE_TIME,EDGE_COUNT,PWM} timer_mode_t;
typedef enum {count_up,count_down} timer_dir_t;

void GPTMClockSet(timer_id_t timer);//tmam mf
void GPTMEnable(timer_wide_t id,timer_status_t state,timer_id_t timer);
void GPTMConfigSet(timer_id_t timer,timer_wide_t id,u16 bit_num,timer_mode_t mode,timer_dir_t dir);
void GPTMLoadSet(timer_id_t timer,timer_wide_t id,u32 value);

#endif /* TIMER_H_ */
