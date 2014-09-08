arduino-analog-read-experiments
===============================

Experiments on reading the analog inputs on the Arduino.

# Blink Two Lights

These files utilize the [Danger Shield](https://www.sparkfun.com/products/11682) although you can get away with just using a few leds and a pot.

 Blinks 2 LEDs in sequence. 
  LED1 H->L
  LED2 H->L
  Optionally, displays a value from 0-9 as well if you are using the Danger Shield.
  
The purpose here is to tweak the reponsiveness of the code so that changes made to the pot/slider is seen in the LEDs as well as the 7 segment display.

Ulitimately, I will be using these for audio circuits driven or controlled by ATTiny chips or maybe even just Mini-pro.  Still, gotta get those chops down and figure out what works well and what does not.

Basically, we are reading a value and blinking a sequence of lights. (and displaying a value from 0-9 on the sheild).
I like the shield because you do not need to break out the breadboard if all you are doing is playing with some sensors and lights. Just slap on the shield and start coding.

## Blink_2_lights_slow.ino

The anti pattern.  Basically, its what you would get if you extended the blink sketch with an analog read.
It works, but as you slide from a fast blink to a slow, its gets sluggish to non-responsive because the delay overrides everything. Once you read a large number, the you delay 4 times to blink.  If you set the pot to a high number and quickly go to zero, it takes four seconds to see the result.

## Blink_2_lights_delay.ino
Nothing too terribly different.  Just added a read between each LED transition.  Much better.

## Blink_2_lights_loop.ino
Much better.  Rather than delay for a long time, chop up the delays into 1 ms intervals and count the time.
You do not need to read all that often really, so you can space that out a bit by masking the timer count.
If this was all you really wanted to do, this would be fine, and you could even increase the number of reads
if you like.

Now, the only reasonable thing to improve is the period.  You do not have as much control here as you think.
The analog read takes time as does the other code, so your frequency may not be exactly accurate.


## TODO interupts




  
 
	
