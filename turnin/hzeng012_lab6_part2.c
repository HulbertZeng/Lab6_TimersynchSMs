 /* Author: Hulbert Zeng
 * Partner(s) Name (if applicable):  
 * Lab Section: 021
 * Assignment: Lab #6  Exercise #2
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=Fsxjq5j3e2o&feature=youtu.be
 */ 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum LG_States { LG_SMStart, LG_State0, LG_State1, LG_State2, LG_Pause } LG_State;

void TickFct_Blink() {
    switch(LG_State) {
        case LG_SMStart:
            LG_State = LG_State0;
            break;
        case LG_State0:
            PORTB = 0x01;
            if((~PINA & 0x01) != 0) {
                LG_State = LG_Pause;
            } else {
                LG_State = LG_State1;
            }
            break;
        case LG_State1:
            PORTB = 0x02;
            if((~PINA & 0x01) != 0) {
                LG_State = LG_Pause;
            } else {
                LG_State = LG_State2;
            }
            break;
        case LG_State2:
            PORTB = 0x04;
            if((~PINA & 0x01) != 0) {
                LG_State = LG_Pause;
            } else {
                LG_State = LG_State0;
            }
            break;
        case LG_Pause:
            if((~PINA & 0x01) != 0) {
                if(PINB == 0x01) {
                    LG_State = LG_State1;
                } else if(PINB == 0x02) {
                    LG_State = LG_State2;
                } else if(PINB == 0x04) {
                    LG_State = LG_State0;
                }
            } else {
                LG_State = LG_Pause;
            }
            break;
        default:
            LG_State = LG_SMStart;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(300);
    TimerOn();
    LG_State = LG_SMStart;
    /* Insert your solution below */
    while (1) {
        TickFct_Blink();
        while(!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
