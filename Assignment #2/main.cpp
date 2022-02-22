#include "mbed.h"

//LEDS
DigitalOut blue(LED1);
PwmOut red(p23);

//Speaker
PwmOut speaker(p24);

//Switches
DigitalIn switch1(p20);
DigitalIn switch2(p19, PullUp);

//Optional Parameters
float period1 = 1.0/960; //960Hz
float period2 = 1.0/1140; //1140Hz

//Program Variables
bool mode = false;
float delta = 1000; //400Hz/0.4sec
float timeStep = 0.01;
float freq = 800; //Hz

int main() {
    red.period(0.0001);
    while(1) {
        //2-tone Siren
        if(switch1 == 1){
            //Select Frequency
            if(mode){
                speaker.period(period1);
            }
            else{
                speaker.period(period2);
            }
            speaker = 0.1; //50% duty cycle
            
            //Set LEDS
            mode ? red = 1.0 : red = 0.0;
            blue = mode;
            
            //Wait and switch states
            wait(0.7);
            mode = !mode;  
        }
        
        //Ascending-Descending tone
        else if(switch2 == 0){ 
            speaker.period(1.0/freq);
            speaker = 0.5;
            
            red = (freq-800.0)/400.0;
            blue = 0;
            
            freq = freq + delta * timeStep;
            wait(timeStep);
            if(freq > 1200 || freq < 800) delta = delta * -1; // Switch States at min/max
        }
        //No Mode Selected
        else{
            speaker = 0;
            red = 1;
            blue = 0;
            freq = 800;
        }
        
    }
}
