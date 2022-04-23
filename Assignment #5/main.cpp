#include "mbed.h"

PwmOut led1(LED1);
PwmOut led2(LED2);

DigitalIn L1up(p24);
DigitalIn L1down(p23);
DigitalIn L2up(p22);
DigitalIn L2down(p21);

DigitalOut led3(LED3);

I2C i2c(p9,p10);

int value1,value2;

void write(int address, int data){
    i2c.start();
    i2c.write(0b10100000); //Command: Write
    i2c.write(address); //Address
    i2c.write(data); //Send Data
    i2c.stop();
    wait(0.01); //Allow stop condition to register
}

int read(int address){
    int out;
    i2c.start();
    i2c.write(0b10100000); //Command: Write (set address pointer)
    i2c.write(address); //Address
    
    i2c.start();
    i2c.write(0b10100001); //Command: Read
    out = i2c.read(0); //collect data
    i2c.stop();
    wait(0.01); //Allow stop condition to register
    return out;
}

int main() {
    led1.period(0.01);
    led2.period(0.01);
    
    //Check for errors
    if(read(1)>5 || read(1)<0) write(1,5);
    if(read(2)>5 || read(2)<0) write(2,5);
    
    while(1){
        //Collect data
        value1 = read(1);
        value2 = read(2);
        
        //Output to LEDs
        led1 = value1/5.0;
        led2 = value2/5.0;
        
        
        //Get LED1 input
        if(L1up == 1 && value1 < 5){
            write(1,value1 + 1);
            wait(0.2); //Debounce
        }
        else if(L1down == 1 && value1 > 0){
            write(1,value1 - 1);
            wait(0.2); //Debounce
        }
        
        //Get LED2 input
        if(L2up == 1 && value2 < 5){
            write(2,value2 + 1);
            wait(0.2); //Debounce
        }
        else if(L2down == 1 && value2 > 0){
            write(2,value2 - 1);
            wait(0.2); //Debounce
        }
        
    }
}
