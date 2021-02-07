 /* Author: Hulbert Zeng
 * Partner(s) Name (if applicable):  
 * Lab Section: 021
 * Assignment: Lab #6  Exercise #3
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://youtu.be/sO7OjLllrf0
 */ 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum AS_States { AS_SMStart, AS_Init, AS_Wait, AS_Increment, AS_Decrement, AS_Reset } AS_State;
unsigned char i = 0x00;

void TickFct_Blink() {
    switch(AS_State) {
        case AS_SMStart:
            AS_State = AS_Init;
            break;
        case AS_Init:
            PORTB = 0x07;
            AS_State = AS_Wait;
            break;
        case AS_Wait:
            if(((~PINA & 0x03) == 0x01) && (i % 10 == 0)) {
                ++i;
                AS_State = AS_Increment;
            } else if(((~PINA & 0x03) == 0x02) && (i % 10 == 0)) {
                ++i;
                AS_State = AS_Decrement;
            } else if((~PINA & 0x03) == 0x03) {
                ++i;
                AS_State = AS_Reset;
            } else {
                i = 0;
                AS_State = AS_Wait;
            }
            break;
        case AS_Increment:
            if(PINB < 9) {
                PORTB = PINB + 1;
            }
            AS_State = AS_Wait;
            break;
        case AS_Decrement:
            if(PINB > 0) {
                PORTB = PINB - 1;
            }
            AS_State = AS_Wait;
            break;
        case AS_Reset:
            PORTB = 0;
            AS_State = AS_Wait;
            break;
        default:
            AS_State = AS_SMStart;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(1000);
    TimerOn();
    AS_State = AS_SMStart;
    /* Insert your solution below */
    while (1) {
        TickFct_Blink();
        while(!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
