/*
This program uses the concept of timers, to blink an LED every second.
*/
#include <avr/io.h>
#include <avr/interrupt.h>

int count=0;
int clock_millisecond=0;

int main(void)
{
     // Enable all interrupts.
     sei();

     // Make all PORTB pins as output
     DDRB |= 0b11111111;

     // CTC mode. Pre-Scale by 64
     TCCR1A|=(1<<COM1A1);
     TCCR1B|=(1<<WGM12)|(1<<CS11)|(1<<CS10);

     // Set the compare value as 250, which corresponds to 1ms.
     OCR1A=250;

     //Enable the Output Compare A interrupt
     TIMSK1|=(1<<OCIE1A); 
     while (1)
     {
	  //do nothing
     }         
}

/**
* This is the interrupt service routine that is automatically trigerred
* every 1 millisecond.
*/
ISR(TIMER1_COMPA_vect)
{
  clock_millisecond++;
  if(clock_millisecond==1000)
  {
         count++;
         if (count==1)
         {
	     PORTB= (1<<PB5);
         }
         else if (count==2)
         {
	     PORTB= 0b00000000;
             count=0;
         }
         clock_millisecond=0;

   }
}