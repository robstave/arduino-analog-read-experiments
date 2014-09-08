
/*
  Blinks 2 LEDs in sequence. 
  LED1 H->L
  LED2 H->L
  
  The purpose here is to tweak the reponsiveness of 
  the code so that changes made to the pot are scene in 
  the LEDS.
  
  This code uses the DangerBoard shield for best effect,
  but you do not need it.  The minimum parts would 
  be a pot and two LEDs.  7 Segment code is outlined.
  
  Version 1.  Sluggish
  Basically...take the blink sketch and extend it
  to make two leds blink.
  The problem here is that Delay ties up the chip
  so once you start the loop, you are commited to 
  at lead 4 times your delay before you can read again.

  Note as you slide the pot from a fast value to a slow
  value, it becomes less and less responsive.  If you 
  slide it from 10 to 0, it takes a long time to see the
  results.
  
  Basically...this is an example of what not to do.
*/

//OPTIONAL 7-Segment
// Shift register bit values to display 0-9 on the seven-segment display
const byte ledCharSet[10] = {
B00111111,
B00000110,
B01011011,
B01001111,
B01100110,
B01101101,
B01111101,
B00000111,
B01111111,
B01101111
};




//The pot is on A0
#define SLIDER1 A0
//LEDs are digital 5 and 6
#define LED1 5
#define LED2 6

//We will limit the delay range a bit so that the LEDS just
//do not blur
#define LEDTIMERLOW 40
#define LEDTIMERHIGH 900

//Optional for 7-seg
#define DATA 4
#define LATCH 7
#define CLOCK 8
 
int sliderValue = 200;

 
// init pins
void setup() {
  // initialize LED and Pot
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT); 
  pinMode(SLIDER1, INPUT);
  
  //setup 7 segement (optional)
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

}


void loop() {
  readSlider1();
  setSevenSegment();
  
  //Toggle LED1
  digitalWrite(LED1, HIGH); 
  delay(sliderValue);
  digitalWrite(LED1, LOW); 
  delay(sliderValue);

  //Toggle LED2       
  digitalWrite(LED2, HIGH); 
  delay(sliderValue);
  digitalWrite(LED2, LOW); 
  delay(sliderValue);
         
  
  
}



/*
  Set the value of the slider to the 7 segement deal
  Optional.
*/
void setSevenSegment() {
     int numToDisplay = map(sliderValue, LEDTIMERLOW, LEDTIMERHIGH, 0,9); //Map the slider value to a displayable value
     digitalWrite(LATCH, LOW);
     shiftOut(DATA, CLOCK, MSBFIRST, ~(ledCharSet[numToDisplay]));
     digitalWrite(LATCH, HIGH);
}


/*
  Read the level on the slider and return a 
  reasonable blink time.
  The slider returns a number from 0 to 1023.
  Superlow numbers just make the led dim.
*/
void readSlider1 () {
   int val1 = analogRead(SLIDER1);  
   sliderValue = map(val1, 0, 1020, LEDTIMERLOW, LEDTIMERHIGH); //Map the slider level to a value we can set on the LED
}
