#include "mbed.h"

SPI spi(p11,p12,p13); 
DigitalOut ss1(p14); //74HC595 mode 0 active low
DigitalOut ss2(p15); //74HC165 mode 2 active high
Timer timer;

int randomNum = 4;
float timeLimit = 1; //Seconds
bool win = false;


void send(char input){
    spi.format(8,0);
    spi.frequency(420000);
    ss1 = 0;
    switch(input){
        case 'A': 
            spi.write(0b11101110);
            break;   
        case 'B': 
            spi.write(0b11111110);
            break;
        case 'C': 
            spi.write(0b10011100);
            break;
        case 'D': 
            spi.write(0b11111100);    
            break;
        case 'L':
            spi.write(0b00011100);
            break;
        case 'E':
            spi.write(0b10011110);
            break;
        default:
            spi.write(input);
            break;
    }
    
    ss1 = 1;
}

int get(){
    ss2 = 1;
    spi.format(8,2);
    spi.frequency(420000);
    int out = spi.write(0);
    ss2 = 0;
    return out;
}

int main() {
    //Start with display off
    send(0);
    
    //Start with both off
    ss1 = 1;
    ss2 = 0;
    
    //Seed the randomness
    srand(time(NULL));
    
    
    while(1>0){
        //Randomize
        randomNum = rand()%4;
    
        //Display the chosen letter
        switch(randomNum){
            case 0: 
                send('A'); 
                break;
            case 1: 
                send('B'); 
                break;
            case 2: 
                send('C'); 
                break;
            case 3: 
                send('D'); 
                break;  
            default:
                send('E'); //Error
                break;  
        }
        
        //Wait for user input
        timer.start();
        timer.reset();
        while(timer.read() < timeLimit){
            if(get() == pow(2.0,randomNum)){
                win = true;
            }   
        }
        timer.stop();
        
        //If the user lost, end the game
        if(!win){
        
        
            //Flash L
            timer.start();
            timer.reset();
            while(timer.read() < 6){
                send('L');
                wait(0.5);
                send(0);
                wait(0.5);
            }
            timer.stop();
            timeLimit = 1;
        }
        
        //Blank output
        send(0);
        wait(1);
        
        //Reset win
        win = false;
        
        //Set the new time
        timeLimit = 0.8*timeLimit;
        
    }
}
