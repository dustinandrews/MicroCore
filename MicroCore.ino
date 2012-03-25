/*
  Blink
  Turns on an outpin on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */


#define latch 0 
#define ser 1
#define sck 2
#define outpin 3
#define load 4


void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an outpin connected on most Arduino boards:
  DDRB = B00011101;
//  pinMode(latch, OUTPUT);
   // pinMode(ser, INPUT);     
//  pinMode(sck, OUTPUT);     
//  pinMode(load, OUTPUT);     
//  pinMode(outpin, OUTPUT);  
  //PORTB |= B00000000;
  PORTB ^= (1<<load);
  
}


void loop() 
{
  static byte dataOut = 0;
  byte dataIn = doInputOutput(dataOut);
  //byte dataIn = doInputOutput(B10101010);
  //You have ~300 bytes on Attiny13 to do your processing and set your output. :)
  dataOut = dataIn ^ 0xFF;
}

byte doInputOutput(byte dataOut)
{
  byte dataIn = 0;
  
  //pulse latch and load pins (in opposition)  
  PORTB ^= (1<<latch);
  PORTB ^= (1<<load);
  delay(1);
  PORTB ^= (1<<latch);
  PORTB ^= (1<<load);
  //delay(1);
  
  byte i = 0;
  byte j = 7;
  for(i = 0; i < 8; i++)
  {
    if((1 << i) & dataOut)
    {PORTB |= (1<<outpin);}
    
    PORTB &= ~(1<<sck);
    delay(1);
    if(PINB & (1<<ser))
    {      
      dataIn = dataIn | (1 << j);
    } 
    j--;
    PORTB |= (1<<sck);
    PORTB &= ~(1<<outpin);   
    //delay(1);
  }
  return dataIn; 
}
