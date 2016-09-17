#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int  flag = 0,i;

void adc_init()
{
  ADMUX |= ((1 << REFS0) | (1 << ADLAR)); //Vcc , left shift adc result
  ADCSRA |= ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); //prescaler 128, enable adc
}
void uwrite(char y)
{
  while (!(UCSR0A&(1<<UDRE0)));
  UDR0=y;
  UCSR0A |= 1<<UDRE0;
}
void utrans(uint16_t d)
{
  UCSR0C |= 1<<UCSZ01 | 1<<UCSZ00 ;  //8 DATA BITS
  UCSR0B |= 1<<TXEN0 ; 
  UBRR0H = d>>8;
  UBRR0L = d;
}
void servo_init()
{
   TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
   ICR1=4999;
   DDRB|=(1<<PB1);
}
void interrupt_init()
{
  EICRA|=(1<<ISC01);
  EIMSK|=(1<<INT0);
}
int adc_read()
{
  ADCSRA |= (1 << ADSC);
  while (ADCSRA != (ADCSRA | (1 << ADIF)));
  ADCSRA |= (1 << ADIF); //clear conversion flag by writing one
  return ADCH;
}

void pwm_init()
{
  TCCR0A = ((1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01)); //set fast pwm to OC0A
  TCCR0B = ((1 << CS00) | (1 << CS02)); //prescale 1024
}

int main()
{
  int  ch,p,q;
  long int z1,z2,x1;
  adc_init();
  pwm_init();
  servo_init();
  interrupt_init();
  sei();
  utrans(104);
  DDRB |= (1<<PB1);
  DDRD |= (1<<PD5)|(1<<PD6);
  OCR1A=500;
  while (1)
  {
    ADMUX |= (1 << MUX0);
    ch = adc_read()+50;
    z1= ch -50 ;
    if(ch>255)
    ch=255;
    OCR0B = ch;
    
   

    ADMUX &= ~(1 << MUX0);
    ch = adc_read()+50;
    z2 = ch - 50 ;
    if(ch>255)
    ch=255;
    OCR0A = ch;
  
    x1=(5000*z1)/255;
    
    p=x1/1000;
    q=x1%1000;
    q/=100;
    uwrite((p + '0'));
    uwrite('.');
    uwrite((q + '0'));



    
    uwrite('\t');

    x1=(5000*z2)/255;
    
    p=x1/1000;
    q=x1%1000;
    q/=100;
    uwrite((p + '0'));
    uwrite('.');
    uwrite((q + '0'));
    uwrite('\n');
   }
}
ISR (INT0_vect)
{ 
  OCR1A=500;//lift panra appo angle
  _delay_ms(1000);
  OCR1A=220;//back to default angle
}
