
#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>

#define CCR_     62500

char it;
char anothertimer;

unsigned long clok;
unsigned int Tmr_frequency;


void initialize_timer (uint32_t smclk);
void enable_timer(void);
void disable_timer(void);

#endif /* TIMER_H_ */
