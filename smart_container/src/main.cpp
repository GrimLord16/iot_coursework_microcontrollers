#include <Arduino.h>
#include <math.h>

int T_int = 0; // Temperature in degrees C
int distance_int = 0; // Distance in cm


char volatile flag = 0, chanel_control = 0; // Timer flag and channel control

char volatile timer = 0;

bool isFanAStarted = false;

unsigned char pwmOCR_A = 255;


// -------------Interrupt Vectors--------------
ISR(TIMER1_COMPA_vect) {
  flag = 1;
  timer++;
  chanel_control ^= 1;
}

ISR(ADC_vect) {

  // Read ADC value
  unsigned int adc_result = ADC; 

  if (chanel_control) {
    // Convert ADC value to voltage
    double V = (adc_result / 1024.0) * 5.0;

    // Convert voltage to temperature in degrees C
    double T = -1481.96 + sqrt(2.1962e6 + (1.8639 - V) / 3.88e-6);

    // Round temperature to integer
    T_int = round(T);

  } else {
    // Convert ADC value to voltage
    double V = (adc_result / 1024.0) * 5.0;

    double distance = 27.86 * pow(V,-1.15);

    distance_int = round(distance);
  }
  }

  

void writeData(){

  Serial.print(T_int);
  Serial.print("/");
  Serial.println(distance_int);
   
}

void setup() {

  
  DDRF = 0x00;
  PORTF = 0b11111100;

  // Configure Timer1
  TCCR1A = 0x00;
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);  // CTC mode & Prescaler @ 1024
  OCR1A = 0x3D08;                                    // compare value = 1 sec (16MHz AVR)
  TIMSK1 |= (1 << OCIE1A);                            // Enable interrupt on OCR1A match

  // Configure ADC
  ADMUX = (1 << REFS0) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);
  MCUCR = (1 << SE) | (1 << SM0); // Enable sleep mode

  

  Serial.begin(9600);


  // //Timer0  -- fast PWM
  TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1) ;
  TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00); // prescaler=
  OCR0A = 0;
  OCR0B = 0;

  //OC_Pins
  DDRB |= 1 << 7;

}

void loop() {

  if (flag) {
    flag = 0;
    ADCSRA |= 1 << ADSC; // Start ADC conversion

    if (chanel_control) ADMUX = (1 << REFS0) | (0 << MUX0);
    else ADMUX = (1 << REFS0) | (1 << MUX0);


    if (timer == 20) {
      timer = 0;
      writeData();
    }
    delay(200);
  }
  if (distance_int >= 40 && !isFanAStarted) {
    OCR0A = pwmOCR_A;
    isFanAStarted = true;
  }

  if (distance_int < 40) {

    OCR0A = 0;
    isFanAStarted = false;
  }

  
}

