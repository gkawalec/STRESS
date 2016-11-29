#ifndef BLINK_H
#define BLINK_H

class Blink
{
    public: 
        Blink();
        unsigned long mark;
        unsigned long target;
        bool on;
        
        
    
    public:
        
        void toggle( int & LED, unsigned long LENGTH);

};

Blink::Blink()
{
    mark = 0;
    target = 0;
    on = FALSE;
}


void Blink::toggle( int& LED ,  unsigned long LENGTH )
{

    if ( mark == 0 && millis() > target ){
        mark = millis();
        target = mark+LENGTH;
        digitalWrite(LED, HIGH);
        Particle.publish("mark", "marked");
    }
    if ( mark != 0 && millis() > target ){
        mark =0;
        target = target+LENGTH; 
        digitalWrite(LED, LOW);
        Particle.publish("mark", "unmarked");

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
