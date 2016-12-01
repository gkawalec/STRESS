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

const unsigned long write_interval = 4000000;
const int HR_numsamples = 8;
int HR_beattime[HR_numsamples] = {0};
int HR_floor = 2400;
int HR_ceiling = 3500;
int HR_bpm = 0;
int HR_pos = 0;


const int AR_numsamples = HR_numsamples*4;
float AR_mag[AR_numsamples] = {0};
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

//    Wire.begin();
//    delay(500);
//    display.prime_all();
    
}    

void loop() {
    
    //Read
    analog_test_x = analogRead(PinX);
    analog_test_y = analogRead(PinY);
    analog_test_z = analogRead(PinZ);
    
    analog_test_output2 = analogRead(HRPin2);
    analog_test_output1 = analogRead(HRPin1);
    analog_test_reference = analogRead(HRPinRef);

    
    int HR_posprev = ( HR_pos+ (HR_numsamples -2) ) % (HR_numsamples -1);

    //collect sample set 
    if (analog_test_output2 > HR_floor){
        if ( micros() - HR_beattime[HR_posprev] > 1050  ){
            blinker.toggle(led, 200000);
            HR_beattime[HR_pos] = micros();
            HR_pos = (HR_pos+1) %(HR_numsamples-1);
        }
    }
    if (micros() > cache.HR_writetime + write_interval - (unsigned long) 500000 ) {
        int i = HR_numsamples-1;
        for ( i; micros() > HR_beattime[i] + write_interval; (i+ HR_numsamples -2)%(HR_numsamples-1) ){
            HR_bpm += (HR_beattime[i]-HR_beattime[(i+ HR_numsamples -2)%(HR_numsamples-1)]);
        }
/*
        for ( int i = 0; i < HR_numsamples - 1; i++){
            HR_bpm += (HR_beattime[i]-HR_beattime[i-1]);
        }
*/
        HR_bpm = HR_bpm/(HR_numsamples - i );
        cache.write( (double) 60000000/HR_bpm, FALSE ) ; //period to BPM;
        HR_bpm = 0;
    }
    blinker.toggle(led, 0);
    
    
    if ( micros() > cache.AR_writetime + 250000){
        AR_mag[AR_pos] = pow(analog_test_x,2)+pow(analog_test_y,2)+pow(analog_test_z,2);
        AR_pos = (AR_pos+1)% (AR_numsamples-1);
    }
    

    if (AR_pos == HR_pos*4 -1 && AR_pos > AR_numsamples - 3) //3 is a fudge factor
    {
        for (int i = 0; i < AR_numsamples -1 ; i++){
            AR_rms += sqrt(AR_mag[i]);
        }
        AR_rms = AR_rms/AR_numsamples;
        cache.write( AR_rms, TRUE);
        AR_rms = 0;
    }
    
    delayMicroseconds(1000);
    
    
    
    
    
    
   // upload();

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


//    display.display(0, display.tf('0'));
//    display.display(1, display.w_dp(display.tf('0')));
//    display.display(2, 0b11000000);
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
