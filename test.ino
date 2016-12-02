SYSTEM_THREAD(ENABLED);

// This #include statement was automatically added by the Particle IDE.
#include "Blink.h"


// This #include statement was automatically added by the Particle IDE.
#include "Upload.h"

// This #include statement was automatically added by the Particle IDE.
#include "Segment.h"

// Code to test for inputs from HR or Accelerometer

#include <cmath>

//Pin Names:
int PinX = A2;
int PinY = A1;
int PinZ = A0;
int HRPin2 = A4;
int HRPin1 = A2;
int HRPinRef = A1;
int led = D6;
int builtinled = D7;

//test values:
int analog_test_x;
int analog_test_y;
int analog_test_z;
int analog_test_output2;
int analog_test_output1;
int analog_test_reference;



int temp =0;
unsigned long nower = 0;

const unsigned long write_interval = 4000000;
const int HR_numsamples = 8;
unsigned long HR_beattime[HR_numsamples] = {0};

//to use 1.75 v and 1.55 V window
int HR_floor = 2150;
int HR_ceiling = 3500;

double HR_bpm = 0;
int HR_pos = 1;
int HR_posprev = 0;


const int AR_numsamples = HR_numsamples*4;
double AR_mag[AR_numsamples] = {0};
double AR_rms = 0;
int AR_pos = 0;


void blink();
bool blinking = FALSE;

Blink blinker;
Segment display;
Upload cache;



void setup() {
    //Accelerometer:
    pinMode(PinZ,INPUT); //z
    pinMode(PinY,INPUT); //y
    pinMode(PinX,INPUT); //x
    //HeartRate: 
    pinMode(HRPin2,INPUT); //Output 2 (Filtered More- if we so choose)
    pinMode(HRPin1,INPUT); //Output 1 
    pinMode(HRPinRef,INPUT); //Reference
    
    // LED
    pinMode(led, OUTPUT);
    pinMode(builtinled, OUTPUT);
    //other way
    //attachInterrupt(HRPin2, blink, RISING);
    
    
    

    //Particle.variable("write", &write, INT);

    //Particle.variable("HR_data", &HR_data, DOUBLE);
    //Particle.variable("AR_data", &AR_data, DOUBLE);

    Wire.begin();
    delay(500);
    display.prime_all();
    
}    

void loop() 
{

    //Read
    analog_test_x = analogRead(PinX) - 2048;
    analog_test_y = analogRead(PinY) - 2048;
    analog_test_z = analogRead(PinZ) - 2048;
    
    analog_test_output2 = analogRead(HRPin2);
    analog_test_output1 = analogRead(HRPin1);
    analog_test_reference = analogRead(HRPinRef);

    
    nower = millis();
    //collect sample set for HR
    if (analog_test_output2 > HR_floor){
        //blink();
        //HR_posprev = ( HR_pos+ (HR_numsamples -2) ) % (HR_numsamples -1);
        if ( nower - HR_beattime[HR_posprev] > 6  ){
            blinker.toggle(led, 200);
            HR_beattime[HR_pos] = nower;
            
            HR_posprev= HR_pos;
            HR_pos = (HR_pos+1) %(HR_numsamples);
            
            

        }
    }
    blinker.toggle(led, 0);
    //Particle.variable("Upload", HR_beattime[7]);
///////////////////////////////////////////////////////////    
    Particle.variable("HR_test", HR_bpm );
////////////////////////////////////////////////////////////    
    
    //collect sample set for AR
    if ( nower > (cache.AR_write_next+250 ) ){
        AR_mag[AR_pos] = pow(analog_test_x,2)+pow(analog_test_y,2)+pow(analog_test_z,2);
        AR_pos = (AR_pos+1) % (AR_numsamples);
        cache.AR_write_next += 250;
        
        //    Particle.publish("AR_mag","over0");
    }
    Particle.variable("AR_test", AR_mag[AR_pos]);
    
    
    //Write to HR cache
    
    if (nower > cache.HR_writetime + write_interval - (unsigned long) 50 ) {
        int i = HR_numsamples-1;
        
        for ( i; nower > HR_beattime[i] + write_interval; (i+ HR_numsamples -1)%(HR_numsamples) ){
            HR_bpm += (HR_beattime[i]-HR_beattime[(i+ HR_numsamples -1)%(HR_numsamples)]);
        }
        

        for ( int i = 0; i < HR_numsamples - 1; i++){
            HR_bpm += (HR_beattime[i]-HR_beattime[i-1]);
        }

        HR_bpm = HR_bpm/(HR_numsamples - i );
        cache.write( (double) 60000.00/HR_bpm, FALSE ) ; //period to BPM;
        //Particle.variable("HR_upload", HR_bpm);
        HR_bpm = 0;
    }
    
    //Write to AR cache
    if (nower > cache.AR_writetime + write_interval - (unsigned long) 50 ){
        //for (int i = 0; i < AR_numsamples -1 ; i++){
        
        for (int i = AR_pos; i < (cache.AR_write_next - cache.AR_writetime)/250 ; (i+AR_numsamples -1) % (AR_numsamples) ){
            AR_rms += sqrt(AR_mag[i]);
        }
        
        AR_rms = AR_rms/AR_numsamples;
        cache.write( AR_rms, TRUE);
        AR_rms = 0;
    }
    
    
    
    delayMicroseconds(1000);
    

/*
        if ( analog_test_output2 > 370) {
        digitalWrite(led, HIGH);
        delay(500);
    }
    if ( analog_test_output2 <= 370) {
        digitalWrite(led, LOW);
    }
*/
    //LED test
    //pin_blink_led(analog_test_output2, 2400, 3500, led);
    // 2000 = 1.623 V
    // test val 370 = 0.3 V    


    display.display(0, display.tf('0'));
    display.display(1, display.w_dp(display.tf('0')));
    display.display(2, 0b11000000);
//delayMicroseconds(1000); // short to find peak
//    blinker.toggle(builtinled, 2000000);


    
}

void blink ()		 
{		
    if ( blinking == false ) {		
        blinking = true;		
        digitalWrite(led, HIGH);		
        delay(200);		
        digitalWrite(led, LOW);		
    }		
}
