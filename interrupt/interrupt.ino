/*
This code uses the concepts of interrupts.
The code toggles the onboard LED whenever an interrupt is triggered in INT0 pin
*/
#include<avr/io.h>
#include<avr/interrupt.h>

void main()
{
  //Make PD2 input mode
  DDRD &= 0x00;

  //Set onboard led as output.(PB13)
  DDRB=0xFF;

  //Enable global interrupts,i.e., enable all interrupts.
  sei();

  //Enable INT0 pin. PD2
  EIMSK|=(1<<INT0);

  //Falling-edge mode for INT0 pin
  EICRA=(1<<ISC01);
  while(1)
  {
    //do nothing
  }
}

/**
*Jumps here automatically when INT0 pin detects a falling edge
*It is the interrupt service routine
*/
ISR(INT0_vect)
{
  //Toggle onboard LED
  PORTB^=(1<<5);

  //Clear the flag
  EIFR|=(1<<INTF0);
}