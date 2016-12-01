#ifndef SEG_H
#define SEG_H

class Segment
{
  public:
    const char accepted[35] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','L','N','O','P','R','S','T','U','W','Y',' ','_','-','\'','^'};
    const char  actual[35] = { 0xC0, 0b01111001, };
    void prime(int address);
    void prime_all();
    void display( int digit, char symbol);
    
    char tf(char symbol);
    char w_dp(char symbol);
    
    
    
    
    
    
    
    
    
};

/* 
For an 8 bit binary digit, on the display directly throught the I2C:

0b01111111 = decimal point  .      
0b10111111 = middle segment -
0b11011111 = top left
0b11101111 = bottom left

0b11110111 = bottom segment _
0b11111011 = bottom right
0b11111101 = top right
0b11111110 = top segment ^
0b11111111 = all off
*/






char Segment::tf(char symbol)
{
    char final = 0xFF;
    int i = 0;
    while (symbol != accepted[i] && i < 35){
        i++;
    }
    if (symbol == accepted[i]){ 
        final == actual[i];
    }
    else
        final = 0b10000000;
    
    return final;
}

char Segment::w_dp(char symbol)
{
    return 0b10000000 ^ symbol;
}





void Segment::prime( int address )
{
    if (!Wire.isEnabled())
        Wire.begin();
    
    Wire.beginTransmission( address );
    // board stuck here ^, no ack to respond and move on
    Wire.write( 6 ); // 
    Wire.write( 0 );
    Wire.endTransmission();
    
    Wire.beginTransmission( address );
    Wire.write( 7 ); // choose 2nd Configuration set of ports
    Wire.write( 0 ); // zero to set configuration ports low
    Wire.endTransmission();
    //two packs sent to enable both IO pins on the expander
}

void Segment::prime_all()
{
    prime(32);
    prime(33);
}


void display3 ( char symbols[3] ) 
{
    
}

void Segment::display ( int digit , char symbol ) 
{
        //0,1,2 digit from right to left
        //33,32,32 IO expander address per digit 
        //2,3,2 IO port set of expander per digit 
        Wire.beginTransmission( 33 - (digit>0) );
        Wire.write( 2 + (digit%2));
        Wire.write( symbol );
        Wire.endTransmission();
}





#endif
