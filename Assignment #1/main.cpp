#include "mbed.h"

BusOut ledArray(LED1,LED2,LED3,LED4);
DigitalIn switch2(p21,PullDown);
DigitalIn switch1(p20,PullUp);
DigitalOut RedLED(p19,1);
DigitalOut GreenLED(p22,0);



int main() {
    //Start all LEDs off
    ledArray = 0; 
    
    //Start bit select on LED 1 (0001)
    int bitSelect = 1;
    
    while(1) {
        //Add LEDS
        if(switch2 && bitSelect<=0b1000){
            ledArray = ledArray + bitSelect; //Add a new LED
            bitSelect = bitSelect * 2;  //Move the bit selector forward
            
            while(!switch1 || switch2); // Wait for user to release button (human error)
            wait(0.01); //Debounce Button
        }
        
        //Remove LEDS
        if(!switch1 && bitSelect>0b0001){
            bitSelect = bitSelect / 2; //Move the bit selector backward
            ledArray = ledArray - bitSelect; //Remove an LED
            
            while(!switch1 || switch2); // Wait for user to release button
            wait(0.01); //Debounce Button
        }
        
        //Full/Empty Indicator LEDS
        if(ledArray == 0b0000) RedLED = 1; //All lights are off -> red LED ON (active high)
        else if(ledArray == 0b1111) GreenLED = 0; //All lights are on -> green LED ON (active low)
        else{
            RedLED = 0;
            GreenLED = 1;
        }
        
        
    }
}
