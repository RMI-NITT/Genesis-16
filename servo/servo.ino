/*
The servo continuously sweeps between set angles, using PWM
*/
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
  int dc=5;

  // Set PORTB as output
  DDRB |= 0xFF;

  // Fast PWM. Non-inverting mode
  TCCR1A |= (1<<WGM11) |( 1<<COM1A1);

  //Prescalar 64
  TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11)|(1<<CS10);

  //For obtaining 50Hz
  ICR1=4999;
  while (1)
  {
      for(dc=125;dc<500;dc++)
      {
          OCR1A=dc;
  	  _delay_ms(5);
      }
      for(dc=499;dc>125;dc--)
      {
  	  OCR1A=dc;
 	  _delay_ms(5);
      }
  }
}