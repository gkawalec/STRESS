// Code to test for inputs from HR or Accelerometer

void blink(void);
void pin_blink_led( const int & , const int &, const int & );
bool blinking = 0;

//Pin Names:
int PinX = A2;
int PinY = A1;
int PinZ = A0;
int HRPin2 = A3;
int HRPin1 = A2;
int HRPinRef = A1;
int led = D7; // builtin led light

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
    pin_blink_led(analog_test_output2, 370, led);
    // 2000 = 1.623 V
    // test val 370 = 0.3 V
    delayMicroseconds(50); // short to find peak
    
    
}

void pin_blink_led( int& PIN , int VALUE, int& LED )
{
    if ( PIN > VALUE ) {
        digitalWrite(LED, HIGH);
        blinking = TRUE;
        delay(500);
    }
    if ( PIN <= VALUE) {
        digitalWrite(LED, LOW);
        blinking = FALSE;
    }

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
