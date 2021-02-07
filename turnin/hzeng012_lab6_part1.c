 /* Author: Hulbert Zeng
 * Partner(s) Name (if applicable):  
 * Lab Section: 021
 * Assignment: Lab #6  Exercise #1
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://youtu.be/veJenaT2qjE
 */ 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum BL_States { BL_SMStart, BL_State0, BL_State1, BL_State2 } BL_State;
unsigned char tempB = 0x00;

void TickFct_Blink() {
    switch(BL_State) {
        case BL_SMStart:
            BL_State = BL_State0;
            break;
        case BL_State0:
            tempB = 0x01;
            BL_State = BL_State1;
            break;
        case BL_State1:
            tempB = 0x02;
            BL_State = BL_State2;
            break;
        case BL_State2:
            tempB = 0x04;
            BL_State = BL_State0;
            break;
        default:
            BL_State = BL_SMStart;
            break;
    }

    PORTB = tempB;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(1000);
    TimerOn();
    BL_State = BL_SMStart;
    /* Insert your solution below */
    while (1) {
        TickFct_Blink();
        while(!TimerFlag);

        TimerFlag = 0;
    }
    return 1;
}
