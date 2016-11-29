// This #include statement was automatically added by the Particle IDE.
#include "Blink.h"

extern float HR_bpm = 0;

// This #include statement was automatically added by the Particle IDE.
#include "Upload.h"

// This #include statement was automatically added by the Particle IDE.
#include "Segment.h"

// Code to test for inputs from HR or Accelerometer

void blink(void);
void pin_blink_led( const int & , const int &, const int &, const int & );
bool blinking = 0;

//Pin Names:
int PinX = A2;
int PinY = A1;
int PinZ = A0;
int HRPin2 = A4;
int HRPin1 = A2;
int HRPinRef = A1;
int led = D6;

//test values:
int analog_test_x;
int analog_test_y;
int analog_test_z;
int analog_test_output2;
int analog_test_output1;
int analog_test_reference;
int write = 0;
double HR_data = 0;
double AR_data =0;
int HR_floor = 2400;
int HR_ceiling = 3500;
int HR_temp = 0;
int temp = 0;

uint16_t HR_avg[16] = {};
uint16_t AR_avg[16] = {}; 

int HR_beattime[16] = {0};
int HR_index = 0;
Blink blinker;



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
    //other way
    //attachInterrupt(HRPin2, blink, RISING);
    

    Particle.variable("Blinking", blinking);
    Particle.variable("write", &write, INT);

    Particle.variable("HR_data", &HR_data, DOUBLE);
    Particle.variable("AR_data", &AR_data, DOUBLE);


    Wire.begin();



}    

void loop() {
    
    blinking = false;
    //Read
    analog_test_x = analogRead(PinX);
    analog_test_y = analogRead(PinY);
    analog_test_z = analogRead(PinZ);
    
    analog_test_output2 = analogRead(HRPin2);
    analog_test_output1 = analogRead(HRPin1);
    analog_test_reference = analogRead(HRPinRef);

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
    
    /* 
    // I2C test
    digitalWrite(led, HIGH);
    Wire.beginTransmission( 32 );
    // board stuck here ^, no ack to respond and move on
    Wire.write( 2 );
    Wire.write( 15 );
    Wire.endTransmission();
    digitalWrite(led, LOW);
    */
    delayMicroseconds(1000); // short to find peak
    blinker.toggle(led, 200);
    
    
    
    int prev = (temp+16) % 16;
    HR_temp = 0;
    if (analog_test_output2 > HR_floor){
        blinker.toggle(led, 200);
        if ( micros() - HR_beattime[prev] > 50  ){
            HR_beattime[temp] = micros();
            temp++;
            temp = temp %16;
        }
    }
    if (temp == 15) {
        for ( int i = 1; i < temp+1; i++){
            HR_temp += (HR_beattime[i]-HR_beattime[i-1]);
        }
        HR_temp = HR_temp/15;
    }
    
    HR_bpm = 60000000/HR_temp; //period to BPM;
    
   // upload();
    
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
