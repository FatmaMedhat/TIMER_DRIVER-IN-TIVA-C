

/**
 * main.c
 */
#include "RegMap.h"
#include "gpio.h"

#include "TIMER.h"
//#define F_BASE  0x4005D000
#define REG volatile unsigned long int *


//volatile unsigned long int * GPIOHBCTL = 0x400FE06C;
//volatile unsigned long int * RCGCTIMER = 0x400FE604;
//volatile unsigned long int * RCGCGPIO = 0x400FE608;
#define FB(offest) (0x40030000+offest)
REG GPTMICR = FB(0x024);//
REG GPTMRIS = FB(0x01C);//

#define F_BASE  0x4005D000

#define OFS(offest) (F_BASE+offest)
//REG GPIODEN_F = OFS(0x51C);
REG GPIODATA_F =  OFS(0x3FC);//
//REG GPIOAFSEL_F =  OFS(0x420);
//REG GPIODIRF =  OFS(0x400);

int main(void)
{

        GPIOClockSet(PORTF_AHB);//tmam mf
        GPIOBusSet(PORTF,AHB);//tmm mf
        GPIODirModeSet(PORTF_AHB, 0xff, MODE_OUT);//tmm mf
        GPIOPadSet(PORTF_AHB,0xff, Drive_8mA, PAD_NPU_NPD);//tmm mf
        GPIOWrite(PORTF_AHB,0xff,0x02);//tmm
        GPTMClockSet(TIMER0);
        GPTMEnable(TIMERA,GPTM_OFF,TIMER0);//dis
        GPTMConfigSet(TIMER0,TIMERA,32,PERIODIC,count_down);
        GPTMLoadSet(TIMER0,TIMERA,0x00f42400);
        GPTMEnable(TIMERA,GPTM_ON,TIMER0);//enable
    while(1){

        if((*GPTMRIS&&0x00000001)){
            *GPTMICR |=(1<<0);
            *GPIODATA_F ^= (1<<1);

        }
    }
	return 0;
}
/*
 * typedef enum {GPTM_OFF,GPTM_ON} timer_status_t;
typedef enum {TIMERA,TIMERB,CONCATENATED} timer_wide_t;
typedef enum {TIMER0,TIMER1,TIMER2,TIMER3,TIMER4,TIMER5} timer_id_t;
typedef enum {ONE_SHOT,PERIODIC,RTC,EDGE_TIME,EDGE_COUNT,PWM} timer_mode_t;
typedef enum {count_up,count_down} timer_dir_t;

void GPTMClockSet(timer_id_t timer);//tmam mf
void GPTMEnable(timer_wide_t id,timer_status_t state,timer_id_t timer);
void GPTMConfigSet(timer_id_t timer,timer_wide_t id,u16 bit_num,timer_mode_t mode,timer_dir_t dir);
void GPTMLoadSet(timer_id_t timer,timer_wide_t id,u32 value);
 */
/**RCGCTIMER |=(1<<0);//timer clk for timer module
*GPTMCTL &= ~(1<<0);//dis timer
*GPTMCFG|= 0x00000000;
*GPTMTAMR|=(0x2<<0);//h5tar periodic
*GPTMTAMR &= ~(1<<4);//dir down
*GPTMTAILR = 0x00f42400; //16 000 000
*GPTMCTL |= (1<<0);//enable timer
while(1){

    if((*GPTMRIS&0x00000001)==1){
        *GPTMICR |=(1<<0);
        *GPIODATA_F ^= (1<<1);

    }
}
return 0;

}
 *
 */
