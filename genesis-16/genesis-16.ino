#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int  flag = 0,i;

// Initialize ADC
void adc_init()
{
  //Vcc is reference voltage, left shift adc result
  ADMUX |= ((1 << REFS0) | (1 << ADLAR));
  
  //Enable adc, prescaler 128
  ADCSRA |= ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
}

/**
 * Set the data to be transmitted by USART
 * @param y The data to be loaded
 */
void uwrite(char y)
{
  // Wait till the transmit buffer is empty, to send the data to the laptop
  while (!(UCSR0A&(1<<UDRE0)));
  
  // Load the data to be transmitted
  UDR0=y;
  
  // Clear the register to be used again
  UCSR0A |= 1<<UDRE0;
}

/**
 * Transmit data throught USART
 * This function initializes the transmittance of data from uno to the lap
 * @param d
 */
void utrans(uint16_t d)
{
  //8 DATA BITS
  UCSR0C |= 1<<UCSZ01 | 1<<UCSZ00 ;
  
  // Enable transmit to the laptop
  UCSR0B |= 1<<TXEN0 ; 

  // Set BAUD rate - 9600
  UBRR0H = d>>8;
  UBRR0L = d;
}

/**
 * Initialize the servo
 */
void servo_init()
{
   // Fast PWM(Mode 14)given by setting WGM bits
   TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
   
   // NON Inverted mode by setting COM1A1, and COM1B1, PRESCALER=64
   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);

   // Set output frequency as 50Hz, as given in servo.
   ICR1=4999;

   // PB1 is output
   DDRB|=(1<<PB1);
}

/**
 * Initialize the interrupt
 */
void interrupt_init()
{
  // Falling edge interrupt for INT0 pin
  EICRA|=(1<<ISC01);

  // Enable interrupt for INT0 pin
  EIMSK|=(1<<INT0);
}

/**
 * Read the adc values
 * @return the read ADC value
 */
int adc_read()
{
  // Start ADC conversion
  ADCSRA |= (1 << ADSC);

  // Wait for ADC conversion to complete.
  while (ADCSRA != (ADCSRA | (1 << ADIF)));

  // Clear conversion flag by writing one
  ADCSRA |= (1 << ADIF); 
  return ADCH;
}

/**
 * Initialize PWM for the wheels of the bot.
 */
void pwm_init()
{
  // Fast PWM by setting WGM pins. Non-inverting mode by setting COM registers.
  TCCR0A = ((1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01));

  // prescale 1024
  TCCR0B = ((1 << CS00) | (1 << CS02));
}

int main()
{
  int  ch,p,q;
  long int z1,z2,x1;
  adc_init();
  pwm_init();
  servo_init();
  interrupt_init();

  // Enable global interrupts
  sei();

  // 104 corresponds to baud rate as 9600
  utrans(104);

  // Servo output is PB1. PD5, and PD6 are wheel outputs.
  DDRB |= (1<<PB1);
  DDRD |= (1<<PD5)|(1<<PD6);

  // Output for servo
  OCR1A=500;
  while (1)
  {
    // ADC1
    ADMUX |= (1 << MUX0);

    // Set each wheels output as ADC values + 50
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

    // Write all the ADC values to the Serial monitor.
  
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

/**
 * Interrupt service routine for the IR module
 */
ISR (INT0_vect)
{ 
  // Angle during lift
  OCR1A=500;
  _delay_ms(1000);

  // Back to default angle
  OCR1A=220;
}
