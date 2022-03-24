#include "mbed.h"

/*
Assignment #3 Microprocessor
Author: Zachary Sasser

Description:
See assignment document
*/

//Hardware Variables
BusOut display(p5,p6,p7,p8,p9,p10,p11,p12);
InterruptIn IC(p26);
InterruptIn IF(p15);
AnalogIn temp(p18);
Serial pc(USBTX, USBRX); // tx, rx


//Internal Variables
int measurement, currentNum, factor;
char unit, outputUnit;


//Collects a specified number of samples from temp sensor and averages them. The return is in volts.
float collect(int samples){
    float sum = 0;
    for(int i = 0; i<samples; i++){
        sum += temp;
    }
    return (sum/samples)*3.3; //3.3 converts to Volts
    
}


//Converts symbol to 7 segment display output.
int convertDisplay(int sym){
    pc.printf("Display: %d \n\r",sym);
    switch(sym){
        case -1: return 0b00000000;
        case 0:  return 0b00111111;
        case 1:  return 0b00000110;
        case 2:  return 0b01011011;
        case 3:  return 0b00001111;
        case 4:  return 0b01100110;
        case 5:  return 0b01101101;
        case 6:  return 0b01111100;
        case 7:  return 0b00000111;
        case 8:  return 0b01111111;
        case 9:  return 0b01101111;
        case 'F':  return 0b01110001; //'F' = 70
        case 'C':  return 0b00111001; //'C' = 67
        case '-':  return 0b01000000;
        case '.': return 0b10000000;
        default: return 0b00000000;
    }
}

//Switches units (used by interupts)
void modeC(void){
    unit = 'C';    
}
void modeF(void){
    unit = 'F';
}



int main() {
    //Setup Interupts
    IC.mode(PullDown);
    IF.mode(PullUp);
    wait(0.5); //Just to be safe
    IC.rise(&modeC);
    IF.fall(&modeF);
    
    unit = 'C'; //Default Unit
    pc.baud(19200); //Baud Rate for Serial Debugging
    
    while(1){
        outputUnit = unit; //In case unit gets switched midway
        
        //Note: measurement forces conversion to int (effectively floor)
        if(outputUnit == 'C'){
            measurement = (collect(1000) - 0.400)/0.0195; 
        }
        else{
            measurement = collect(1000)*92.3076923077 - 68.9230769231;
        }
         
        //Output the number
        factor = log10f(measurement); //Determines what power of 10 the most significant digit is
        while(factor>=0){
            //Calculate most significant digit
            currentNum = measurement/powf(10,factor);//Calculates the next most significant number
            
            //Display number for 0.5 - 1.0 seconds
            display = convertDisplay(currentNum);
            wait(0.75);
            
            //Blank for 0.1 seconds
            display = convertDisplay(-1);
            wait(0.1);
            
            //Remove that digit from number.
            measurement -= currentNum*powf(10,factor);
            
            //Move digit selection factor
            factor -=1;
        }
        
        //Display Unit
        display = convertDisplay(unit);
        wait(0.75);
        display = convertDisplay(-1);
        wait(0.1);
        
    }
}
