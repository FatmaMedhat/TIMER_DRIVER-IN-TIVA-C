/*
 * TIMER.c
 *
 *  Created on: Apr 14, 2020
 *      Author: DELL
 */
#include "TIMER.h"
#include "std_types.h"
#include "RegMap.h"

void GPTMClockSet(timer_id_t timer){
    //volatile u32  *reg1 = ((timer*1000)+0x40030000 + RCGCTIMER);
    volatile u32  *reg1 = ( (timer*1000)+RCGCTIMER);
               *reg1 |=(1<<timer);//tm



}

void GPTMEnable(timer_wide_t id,timer_status_t state,timer_id_t timer){
    volatile u32  *reg1 = ((timer*1000)+0x40030000 + GPTMCTL);
            if(id==TIMERA&&state==GPTM_ON){
                   *reg1 |= (1<<0);

            }else if(id==TIMERB&&state==GPTM_ON){

                   *reg1 |= (1<<8);
            }else if(id==TIMERA&&state==GPTM_OFF){//tm

                    *reg1 &= ~(1<<0);
            }else if(id==TIMERB&&state==GPTM_OFF){

                    *reg1 &= ~(1<<8);
            }


}
//typedef enum {ONE_SHOT,PERIODIC,RTC,EDGE_TIME,EDGE_COUNT,PWM} timer_mode_t;
void GPTMConfigSet(timer_id_t timer,timer_wide_t id,u16 bit_num,timer_mode_t mode,timer_dir_t dir){

    volatile u32  *reg1 = ((timer*1000)+0x40030000 + GPTMCFG);
    volatile u32  *reg2 = ((timer*1000)+0x40030000 + GPTMTAMR);
    volatile u32  *reg3 = ((timer*1000)+0x40030000 + GPTMTBMR);
    volatile u32  *reg4 = ((timer*1000)+0x40030000 + GPTMCTL);
if(id==TIMERA){
    if(mode==ONE_SHOT){
        *reg1|=0x00000000;
        *reg2|=(0x1<<0);

    }else if(mode==PERIODIC){
        *reg1|=0x00000000;//tm
        *reg2|=(0x2<<0);//tm
    }else if(mode==RTC){
        *reg1|=0x00000001;
    }else if(mode==EDGE_TIME){
        *reg1|=0x00000004;
        *reg2|=(0x3<<0);
        *reg2|=(0x1<<2);
    }else if(mode==EDGE_COUNT){
        *reg1|=0x00000004;
        *reg2|=(0x0<<2);
    }else if(mode==PWM){
        *reg1|=0x00000004;
        *reg2|=(0x0<<2);
        *reg2|=(0x2<<0);
    }
    if(dir==count_up){

            *reg2|=(1<<4);

        }else if(count_down){

            *reg2 &= ~(1<<4);//tm
        }
}else if(id==TIMERB){

        if(mode==ONE_SHOT){
            *reg1|=0x00000000;
            *reg3|=(0x1<<0);
        }else if(mode==PERIODIC){
            *reg1|=0x00000000;
            *reg3|=(0x2<<0);
        }else if(mode==RTC){
            *reg1|=0x00000001;
        }else if(mode==EDGE_TIME){
            *reg1|=0x00000004;
            *reg3|=(0x3<<0);
            *reg3|=(0x1<<2);
        }else if(mode==EDGE_COUNT){
            *reg1|=0x00000004;
            *reg3|=(0x0<<2);
        }else if(mode==PWM){
            *reg1|=0x00000004;
            *reg3|=(0x0<<2);
            *reg3|=(0x2<<0);
        }
    if(dir==count_up){

        *reg3|=(1<<4);

    }else if(count_down){

        *reg3 &= ~(1<<4);
    }

}



}

void GPTMLoadSet(timer_id_t timer,timer_wide_t id,u32 value){


    if(id==TIMERA)
    {
        volatile u32  *reg1 = ((timer*1000)+0x40030000 + GPTMTAILR);
        *reg1=value;//tm
    }
    else if(id==TIMERB)
    {
        volatile u32  *reg1 = ((timer*1000)+0x40030000 + GPTMTBILR);
        *reg1=value;
    }



}





