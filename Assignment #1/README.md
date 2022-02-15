Note that there are both active-high as well as active-low switches and LEDs. This will give you 
practice with all of the cases.

Initially, the 4 blue LEDs built into the mbed itself should be off. Each time Switch 2 is pressed, 
one of the blue LEDs that is off should be turned on. Each time Switch 1 is pressed, one of the 
blue LEDs that is on should be turned off. In either case, if there are no blue LEDs in the 
appropriate state (off for Switch 2 or on for Switch 1) then nothing should change.
The red LED should be on if and only if all of the blue LEDs are off. The green LED should be 
on if and only if all of the blue LEDs are on.

You may assume that no more than one switch is pressed at a time. The program should be 
usable on a human time scale (either look for a press/release cycle, or ensure that if a switch is 
held down it does not repeat the associated action faster than once per 500 ms). Be sure to 
compensate for spurious edges due to switch bounce. The program should be written to use the 
DigitalIn and DigitalOut classes from mbed OS 2 (state with the “Blinky LED Hello World” 
template
