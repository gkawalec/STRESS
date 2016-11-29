#ifndef BLINK_H
#define BLINK_H

class Blink
{
    public: 
        Blink();
        unsigned long int mark;
        
        
    
    public:
        
        void toggle( int & LED, unsigned long int LENGTH);

};

Blink::Blink()
{
    mark = 0;
}


void Blink::toggle( int& LED ,  unsigned long int LENGTH )
{

    if ( mark == 0 ){
        mark = millis();
        digitalWrite(LED,HIGH);
    }
    else if ( millis() >= mark + LENGTH){
        digitalWrite(LED,LOW);
        mark =0;
    }


/*
    if ( PIN >= CEILING && PIN <= FLOOR) {
        digitalWrite(LED, LOW);
        blinking = FALSE;
    }
    else {
        digitalWrite(LED, HIGH);
        blinking = TRUE;
        
    }
*/

}










#endif
