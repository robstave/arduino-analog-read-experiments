/*
    Blinks 2 LEDs in sequence. 
  LED1 H->L
  LED2 H->L
  Optionally, displays a value from 0-9 as well
  
  The purpose here is to tweak the reponsiveness of 
  the code so that changes made to the pot are scene in 
  the LEDS.
  
  This code uses the DangerBoard shield for best effect,
  but you do not need it.  The minimum parts would 
  be a pot and two LEDs.  7 Segment code is outlined.
  
  Version 3.
  This is another improvement on responsiveness.
  Now, there is no lengthy delay.
  The slider is read every 32 loops (32 ms)
  This value is used for the counter to reset 
  and evaluate the LED states.

  Changes on the slider are acted on much faster.

  Technically, the chip is still doing an equivalent
  amount of delay time, but its just chopped up more for
  you to do things.  Its not like this is taking a 
  lot of cpu  
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

//Use this as a counter for when to check things
int counter = 0;

int sliderValue = 200;

//Toggle LEDs by state rather than loop code
byte ledState = 0;

// init pins
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT); 
  pinMode(SLIDER1, INPUT);
  
  //setup 7 segement
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

  
}

// the loop function runs over and over again forever
void loop() {
  
  //When we count up to the value of the slider, do some stuff. 
  if (counter > sliderValue) {
    
    
    counter = 0;  //reset counter
    ledState++;   //increment state
 
    byte state = ledState & 3;
   
    switch(state) {
    case 1:
         digitalWrite(LED1, LOW); 
         digitalWrite(LED2, HIGH); 
         break;
    case 3:
         digitalWrite(LED1, HIGH); 
         digitalWrite(LED2, LOW);
         break; 
    default:
         digitalWrite(LED1, LOW); 
         digitalWrite(LED2, LOW); 
    }
  
  }
  
  //No need to read the slider that often
  if (counter & 31) {
    readSlider1();
  }
   
   
  if (counter & 127) {
     //so this is just under 10 times a second.
     //Really no need to do more.
      setSevenSegment();
  }
  
  counter++;
  delay(1);
}


/*
  Set the value of the slider to the 7 segement deal
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
