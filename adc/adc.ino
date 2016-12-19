/*
A simple code that uses the concepts of ADC and PWM,
to control the brightness of an LED using a potentiometer.
*/
#include <avr/io.h>
#include <stdlib.h>

/**
* A function to initialize Analog to Digital Conversion
*/
void adc_initialize()
 {
     //Setting reference voltage as VCC
     ADMUX = (1<<REFS0);

     //enable ADC. Pre-scale by factor of 64
     ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
 }

/**
* A function to initialize Timer1
*/
 void timer1_init()
 {
    //Fast PWM mode 10-bit. Non-inverting mode
    TCCR1A |=  (1 << WGM11)|(1<<WGM10)|(1<<COM1A1);

    //Prescale by 8
    TCCR1B|=(1 << CS11)|(1 << WGM12);
}

int main(void)
{  
	// Configure PortB as output (all 1)
	DDRB = 0xFF;

	// Configure PortC as input.PC0 is ADC0
	DDRC |= 0x00;

	//Call the functions to initialize the timer and ADC				
	timer1_init();
     	adc_initialize();				
	while(1)
	{
		//start conversion
    		ADCSRA |= (1<<ADSC); 

		//Wait until conversion is over, i.e., the flag is set.
     		while(!(ADCSRA & (1<<ADIF)));  

		//clear flag
	 	ADCSRA|=(1<<ADIF);

		// Set the PWM value to the value read by ADC
	 	OCR1A=ADC;
	}
} 