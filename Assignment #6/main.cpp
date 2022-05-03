
/*
TODO:

Add title comment
Fix int to void on setters
define a wait function
Test program on hardware
*/

//sw1 p14 P0.16 PINMODE1.0 Pull-down
//sw2 p27 P0.11 PINMODE0.22 Pull-down
//r1 p16 P0.24
//r2 p17 P0.25
//b1 P1.18 
//b2 P1.20
//b3 P1.21
//b4 P1.23
//g1 p24 P2.2
//g2 p23 P2.3

volatile int dummy = 0;

// Registers for port 0 
#define FIO0DIR (*(volatile unsigned int *)0x2009c000) 
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)

// Registers for port 1 
#define FIO1DIR (*(volatile unsigned int *)0x2009c020) 
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)

// Registers for port 2 
#define FIO2DIR (*(volatile unsigned int *)0x2009c040) 
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)

// Pinmodes
#define PINMODE0 (*(volatile unsigned int *)0x4002c040) 
#define PINMODE1 (*(volatile unsigned int *)0x4002c044)

void wait(float t){
    volatile int count = t * 21.33e6;
    while(count>0) {
        count--;
    }
}

int getMove(){
    //Gather the register first so the game is fair
    volatile unsigned int input = FIO0PIN; 
    
    //SW1 - SW2 = movement increment
    return ((input >> 16) & 1) - ((input >> 11) & 1);
}

//r1 p16 P0.24
void setR1(int state){
    if(state)
        FIO0PIN |= (1<<24);
    else
        FIO0PIN &= ~(1<<24);    
    dummy++;
}


//r2 p17 P0.25
void setR2(int state){
    if(state)
        FIO0PIN |= (1<<25);
    else
        FIO0PIN &= ~(1<<25);    
    dummy++; 
}

//b1 P1.18 
void setB1(int state){
    if(state)
        FIO1PIN |= (1<<18);
    else
        FIO1PIN &= ~(1<<18); 
    dummy++;    
}

//b2 P1.20
void setB2(int state){
    if(state)
        FIO1PIN |= (1<<20);
    else
        FIO1PIN &= ~(1<<20);  
    dummy++;   
}

//b3 P1.21
void setB3(int state){
    if(state)
        FIO1PIN |= (1<<21);
    else
        FIO1PIN &= ~(1<<21);  
    dummy++;       
}

//b4 P1.23
void setB4(int state){
    if(state)
        FIO1PIN |= (1<<23);
    else
        FIO1PIN &= ~(1<<23);  
    dummy++;       
}

//g1 p24 P2.2
void setG1(int state){
    if(state)
        FIO2PIN |= (1<<2);
    else
        FIO2PIN &= ~(1<<2);  
    dummy++;       
}

//g2 p23 P2.3
void setG2(int state){
    if(state)
        FIO2PIN |= (1<<3);
    else
        FIO2PIN &= ~(1<<3);  
    dummy++;       
}

void initializePins(void){
    //sw1 p14 P0.16 PINMODE1.0 Pull-down
    FIO0DIR &= ~(1<<16);
    PINMODE1 |= (1<<0) | (1<<1);
    
    //sw2 p27 P0.11 PINMODE0.22 Pull-down
    FIO0DIR &= ~(1<<11);
    PINMODE0 |= (1<<22) | (1<<23);
    
    //r1 p16 P0.24
    FIO0DIR |= (1<<24);
    
    //r2 p17 P0.25
    FIO0DIR |= (1<<25);
    
    //b1 P1.18 
    FIO1DIR |= (1<<18);
    
    //b2 P1.20
    FIO1DIR |= (1<<20);
    
    //b3 P1.21
    FIO1DIR |= (1<<21);
    
    //b4 P1.23
    FIO1DIR |= (1<<23);
    
    //g1 p24 P2.2
    FIO2DIR |= (1<<2);
    
    //g2 p23 P2.3
    FIO2DIR |= (1<<3);
    
    //Allow pinmodes to set   
    wait(0.001);  
}

//-1 = red wins; 0 = in progress; 1 = green wins
int setRope(int pos){
    //Set everything to zero so we can update
    setR1(0); setR2(0); setB1(0); setB2(0); setB3(0); setB4(0); setG1(0); setG2(0);
    

    switch(pos){
    case 0: 
        setR1(1);
        setR2(1);
        return -1;
    case 1: 
        setR2(1);
        setB1(1);
        break;  
    case 2: 
        setB1(1);
        setB2(1);
        break;  
    case 3: 
        setB2(1);
        setB3(1);
        break;   
    case 4: 
        setB3(1);
        setB4(1);
        break;  
    case 5: 
        setB4(1);
        setG1(1);
        break;  
    case 6: 
        setG1(1);
        setG2(1);
        return 1;  
         
    }
    return 0;    
}

int main() {
    initializePins();
    
    int pos = 3;
    setRope(pos);
    
    
    while(setRope(pos) == 0){
        pos+=getMove();
        while(getMove()!=0); //debounce
    }
    
    if(pos>=6){
        while(1) {
            setRope(pos++);
            if(pos >= 6) pos = 0;
            wait(0.2);
        }      
    }
    if (pos<=0){
        while(1) {
            setRope(pos--); 
            if(pos <= 0) pos = 6;
            wait(0.2);
        } 
    }
    
    
}
