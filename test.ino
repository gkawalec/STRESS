//SYSTEM_THREAD(ENABLED);

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

const unsigned long write_interval = 4000;
const int HR_numsamples = 8;
unsigned long HR_beattime[HR_numsamples] = {0};

//to use 1.75 v and 1.55 V window
// 2048 = half of V_supply = 1.67 V
int HR_floor = 2150; // 2100/1226 = 1.713 V
int HR_ceiling = 3500;

double HR_bpm = 0;
int HR_pos = 1;
int HR_posprev = 0;


const int AR_numsamples = HR_numsamples*4;
double AR_sq[AR_numsamples] = {0};
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
    
    
    
    Particle.variable("Stress", cache.upload);
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
    // 2048 for centre point
    analog_test_x = (analogRead(PinX) - 2048);
    analog_test_y = (analogRead(PinY) - 2048);
    analog_test_z = (analogRead(PinZ) - 2048);
    
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
            display.toggle_dp(200000);
            HR_beattime[HR_pos] = nower;
            
            HR_posprev= HR_pos;
            HR_pos = (HR_pos+1) %(HR_numsamples);
            
            

        }
    }
    

    //collect sample set for AR
    if ( nower > (cache.AR_write_next+250 ) ){
        AR_sq[AR_pos] = pow(analog_test_x,2)+pow(analog_test_y,2)+pow(analog_test_z,2);
        AR_pos = (AR_pos+1) % (AR_numsamples);
        cache.AR_write_next += 250;
        
        //    Particle.publish("AR_mag","over0");
    }


    
    //Write to HR cache
  /* 
    if (nower > (cache.HR_writetime + write_interval) ) {
        
        int i = HR_pos;
        HR_bpm = 0;
        
        for ( i; HR_beattime[i] > nower - write_interval; i= (i+ HR_numsamples -1)%(HR_numsamples) ){
           HR_bpm += (double)  HR_beattime[i]-HR_beattime[(i+ HR_numsamples -1)%(HR_numsamples)] ;
        }
        //HR_bpm = abs(HR_beattime[HR_pos]-HR_beattime[HR_posprev]);

        //for ( int i = 0; i < HR_numsamples - 1; i++){
        //    HR_bpm += (HR_beattime[i]-HR_beattime[i-1]);
        //}

        HR_bpm = HR_bpm/(HR_numsamples - 1 );
        //cache.HR_writetime = nower;
        cache.write( (double) 600.00/HR_bpm, FALSE ) ; //period to BPM;
        //Particle.variable("HR_upload", HR_bpm);
        //

        
    }
  */
    
    if (nower > (cache.HR_writetime + write_interval) ) {
        
        HR_bpm = abs(HR_beattime[HR_pos]-HR_beattime[HR_posprev]);

        cache.write( (double) 600.00/HR_bpm, FALSE ) ; //period to BPM;
        
    }
    
    
    //Write to AR cache
    
    if (nower > cache.AR_writetime + write_interval ){
        //for (int i = 0; i < AR_numsamples -1 ; i++){
        
        AR_rms = 0;
        int count =0;
        for (int i = AR_pos; count*250 < abs(cache.AR_write_next - cache.AR_writetime); i= (i+AR_numsamples -1) % (AR_numsamples) ){
            AR_rms += sqrt(AR_sq[i]);
            count++;
        }
        
        
        AR_rms = AR_rms / (count * 409.6 *1.0432); //0.1*4096 is conversion factor to g == 9.81m/s; 1.0432 for chip specfic error 
        //cache.AR_writetime = nower;
        //AR_rms = AR_rms/ (AR_numsamples *409.6); //0.1*4096 is conversion factor to g == 9.81m/s
        cache.write( AR_rms, TRUE);

    }
    
    /*
    if (nower > cache.AR_writetime + write_interval ){
        
        AR_rms = sqrt(AR_sq[AR_pos]) / (409.6 *1.0432); //0.1*4096 is conversion factor to g == 9.81m/s; 0.9585 for chip specfic error 

        cache.write( AR_rms, TRUE);

    }
    
    */
    
    
/*
    
    if (nower % 60000 < 100){
        cache.publish();
        delay(100);
    }
    
    
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

    
    if (nower % 500 < 100){
        display.display(0, 0b11011110);
        display.display(1, 0b10101111);
        display.display(2, 0b11110111);
        

  
    
    }
    blinker.toggle(led, 0);
    display.toggle_dp(0);
    
    delayMicroseconds(1000); // short to find peak
    
    
    
    
///////////////////////////////////////////////////////////    
   //Particle.variable("HR_test",  HR_beattime[HR_pos]);
   Particle.variable("HR_test", HR_bpm);
   //Particle.variable("HR_test", (int) abs( HR_beattime[HR_pos]- HR_beattime[HR_posprev] ));
   //Particle.variable("AR_test", AR_rms);
///////////////////////////////////////////////////////////
    
    
    

    
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
