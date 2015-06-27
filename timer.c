//smclok 1mhz için düzgün çalýþýyor

#include "msp430g2553.h"
#include <stdint.h>
#include "timer.h"


void initialize_timer (uint32_t smclk){
TA0CTL = TASSEL_2 + MC_2+ ID_3; 	// SMCLK + Upmode + divider/8 (SMCLK/8)
Tmr_frequency=(smclk/8)/CCR_;      //(1mhz/8)/62500=2  =0.5s =500ms
//Tmr_frequency deðerinde cýkan sonuc (X) kez interrupta girerse 1 sn geçer .
clok=smclk;
}

void enable_timer(void){
    TA0CTL = TASSEL_2 + MC_2+ ID_3;
    TA0CCR0 = CCR_;
    TA0CCTL0 |= CCIE;
}
void disable_timer(void){
    TA0CTL = MC_0;       // timer halted
    TA0CCTL0 &=~CCIE;
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P2OUT^= BIT2;
    it++;
    if(it==5){P2OUT^= BIT1;it=0;anothertimer=1;TA0CCTL0 &=~CCIE;TA0CTL = MC_0;__bic_SR_register_on_exit (CPUOFF);}
    TA0CCR0 += CCR_;
}
