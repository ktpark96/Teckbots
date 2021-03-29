#define F_CPU 16000000
   #include <avr/io.h>
   #include <util/delay.h>
   #include <avr/interrupt.h>


    void Forward(uint8_t speed);
    void Backward(uint8_t speed);
    void Left(uint8_t speed);
    void Right(uint8_t speed);
    void Stop(uint8_t speed);
    void LeftForward(uint8_t speed);
    void RighttForward(uint8_t speed);


   #define OC1A_WIDTH OCR1A
   #define OC1_PERIOD ICR1

   enum tone_scale{
         No, Do, Rae, Mi, Pa, Sol, Ra, Si, Do_7
   };

   uint16_t frequency_return(uint16_t fre);
   void tone0(uint8_t scale);
   void tone1(uint8_t scale);
   void tone2(uint8_t scale);
   void tone3(uint8_t scale);

   void startbuzzer();
   void leftbuzzer();
   void rightbuzzer();
   void bothbuzzer();

    uint16_t tone_array[9] = {0,1046,1174,1318,1396,1567,1760,1975, 2093}; //Do, Rae ...

   ISR(TIMER3_OVF_vect)
   {
    TCNT3 = 0xffff - 7812; // Every 1 second
   PORTD |= (1 << 6); 
   _delay_ms(10);
   PORTD |= (0 << 6);
   _delay_ms(10);


  
   }

 int main()
   {

   DDRB = 0b10101100; //PB7, PB3, PB2 : OUTPUT
   DDRD = 0b01000111; //PD6, PD2, PD1, PD0 : OUTPUT
  // DDRF = 0b11111100; //PF0, PF1 : INPUT
   DDRF = 0x00;
   PORTF = 0b00000011; // INTERNAL PULL UP

   TCCR1A = 0b10000000; // PWM, OC1A On, Phase and Frequency Correct
   TCCR1B = 0b00010010; //prescaler 8   

   TCCR0A = 0b11110001; // PWM, Phase and Frequency Correct
   TCCR0B = 0b00000100; // Prescaler : 256
   TCCR3A = 0b00000000; // Normal
   TCCR3B = 0b00000101; //prescaler 1024
   TIMSK3 = 0b00000001;
   TCNT3 = 0xffff-7812; // Every 1 second
   


  

sei();
  int a = 1;

  while(a) {
   if((PINF & 0b00000010) == 0){
      Stop(0);
   }
   else{
        Stop(0);
   }

   if((PINF & 0b00000001) == 0)
   {
      Stop(0);
   }
   else{
        Stop(0);
   }
   if((PINF & 0b00000011) == 0)
   {
      startbuzzer();
      a--;
      break;
   }
}

  
   while((a == 0)){
   _delay_ms(10);
   if((PINF & 0b00000011) == 0){ // both-switch
    Stop(0);
    _delay_ms(1);
   bothbuzzer();
   _delay_ms(5); 
   Backward(130);
   _delay_ms(250);
   Left(100);
   _delay_ms(150); 
   
   }

   else if((PINF & 0b00000001) == 0) //left switch
   {
   Stop(0);
   _delay_ms(1); 
   leftbuzzer();
   _delay_ms(5); 
   Backward(130);
   _delay_ms(150); 
    //Right(200);
   RightForward(150);
   _delay_ms(100); 
   }

   else if((PINF & 0b00000010) == 0) // Right switch
   {
    Stop(0);
    _delay_ms(1);
   rightbuzzer();
   _delay_ms(5); 
   Backward(130);
 _delay_ms(200); 
   LeftForward(150);
   _delay_ms(100);
   }

   else 
   {

   Forward(100);
   _delay_ms(1);
   }

   }

    return 0;
   }



void Forward(uint8_t speed) //Function for moving forward robot. Speed : 0 ~ 255
   {
   PORTB = 0b10001000;
   PORTD = 0b00000101;
   OCR0A = speed ;//right wheel
   OCR0B = speed ;//left wheel
 


   }

void Backward(uint8_t speed) //Function for moving backward robot. Speed : 0 ~ 255
   {
   PORTB = 0b10000100;
   PORTD = 0b00000011;
    OCR0A = speed;
   OCR0B = speed;

   }
void Left(uint8_t speed) //Function for moving robot. Speed : 0 ~ 255
   {
   PORTB = 0b10001000;
   PORTD = 0b00000011;
   OCR0A = speed;
   OCR0B = speed;
   }
void Right(uint8_t speed) //Function for moving robot. Speed : 0 ~ 255
   {
   PORTB = 0b10000100;
   PORTD = 0b00000101;
   OCR0A = speed;
   OCR0B = speed;
   }
 void Stop(uint8_t speed) //Function for moving robot. Speed : 0 ~ 255
   {
   PORTB = 0b00000000;
   PORTD = 0b00000000;
   OCR0A = speed;
   OCR0B = speed;
   }
   void LeftForward(uint8_t speed) //Function for moving leftforward robot. Speed : 0 ~ 255
   {
   PORTB = 0b10001000;
   PORTD = 0b00000101;
   OCR0A = speed-100;
   OCR0B = speed + 100;
   }

   void RightForward(uint8_t speed) //Function for right forward robot. Speed : 0 ~ 255
   {
   PORTB = 0b10001000;
   PORTD = 0b00000101;
   OCR0A = speed + 100;
   OCR0B = speed-100;
   }




void startbuzzer()
   {
   tone2(Sol);
   tone0(No);
   tone2(Sol);
   tone0(No);
   tone2(Ra);
   tone0(No);
   tone2(Ra);
   tone0(No);
   tone2(Sol);
   tone0(No);
   tone2(Sol);
   tone0(No);
   tone2(Mi);
   tone0(No);
   }

   void leftbuzzer()
   {
   tone2(Do);
   tone0(No);
   tone2(Rae);
   tone0(No);
   tone2(Mi);
   tone0(No);
   tone2(Pa);
   tone0(No);
   
   }

   void rightbuzzer()
   {
   tone2(Pa);
   tone0(No);
   tone2(Mi);
   tone0(No);
   tone2(Rae);
   tone0(No);
   tone2(Do);
   tone0(No);
   }

   void bothbuzzer()
   {
   tone2(Sol);
   tone0(No);
   tone2(Sol);
   tone0(No);
   tone2(Sol);
   tone0(No);
   tone2(Sol);
   tone0(No);
   }

   uint16_t frequency_return(uint16_t fre) // PWM Period to Frequency
   {
    int8_t period_1 = 2; // period 2us
    int set_period = 0;
    int16_t return_fre = 0;

    set_period = 1000000 / fre;
    return_fre = set_period /period_1;

    return return_fre;
   }


  void tone0(uint8_t scale) 
   {
   OC1_PERIOD = frequency_return(tone_array[scale]); //period 
   OC1A_WIDTH = frequency_return(tone_array[scale])/20; //width
   _delay_ms(10);
   }
  void tone1(uint8_t scale) 
   {
   OC1_PERIOD = frequency_return(tone_array[scale]); //period 
   OC1A_WIDTH = frequency_return(tone_array[scale])/20; //width
   _delay_ms(20);
   }
   void tone2(uint8_t scale) 
   {
   OC1_PERIOD = frequency_return(tone_array[scale]); //period 
   OC1A_WIDTH = frequency_return(tone_array[scale])/20; //width
   _delay_ms(40);
   }
   void tone3(uint8_t scale) 
   {
   OC1_PERIOD = frequency_return(tone_array[scale]); //period 
   OC1A_WIDTH = frequency_return(tone_array[scale])/20; //width
   _delay_ms(80);
   }