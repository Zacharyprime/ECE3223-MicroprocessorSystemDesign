In this assignment you will use the DigitalIn and PwmOut interfaces on the mbed 
microcontroller board to implement sound effects and blinking LEDs for a toy emergency 
vehicle.

Connect two pushbutton switches, one between the mbed’s p20 and VOUT and another between 
p19 and GND. Connect a red LED in series with a 220 ohm resistor between the mbed’s p23 
and VOUT (the LED’s anode should be oriented towards VOUT). Connect the piezo transducer (it
looks like a small black cylinder with a hole at the top to emit sound) between the mbed’s p24 
and GND. 

The mbed should start in an idle mode in which all of the LEDs are off and the piezo transducer 
is silent. If either switch is pressed, the mbed begins one of two different effects, one effect for 
each switch. When no effects are active, the mbed should return to the idle mode.
If the switch connected to p20 is pressed, the mbed should generate a two tone siren effect and 
repeat the effect until the switch is released. During this effect the piezo transducer should 
generate a 960 Hz tone for 0.7 seconds followed by a 1140 Hz tone for 0.7 seconds. Synchronized
with this sound effect, the red LED and the built-in blue LED1 should alternately flashing 
on and off. When the piezo is generating 1140 Hz, the red LED should be off and the blue LED 
on. When the piezo is generating 960 Hz, the red LED should be on and the blue LED off.

If the switch connected to p19 is pressed, the mbed should generate a warbling siren effect and 
repeat the effect until the switch is released. During this effect the piezo transducer should 
generate ascending frequencies from 800 Hz to 1200 Hz over the span of 0.4 seconds and then
descending frequencies from 1200 Hz to 800 Hz, also over the span of 0.4 seconds. 
Synchronized with this sound effect, red LED should smoothly transition from fully off when the
piezo is generating 800 Hz, to fully on when the piezo is generating 1200 Hz. For both the 
piezo and the LED, the changes in frequency and brightness should occur in small enough steps 
that it appears to a human to be a continuous transition rather than discrete steps.

To simplify the programming, you need only check for a switch release once per cycle of each 
effect rather than continuously. You may also assume that only one switch will be pressed at a 
time.