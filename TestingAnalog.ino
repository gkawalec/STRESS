// Code to test for inputs from HR or Accelerometer

void blink(void);
void pin_blink_led( const int& PIN , const int& VALUE, const int& LED )
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
}    

void loop() {
    
    //Read
    analog_test_x = analogRead(PinX);
    analog_test_y = analogRead(PinY);
    analog_test_z = analogRead(PinZ);
    
    analog_test_output2 = analogRead(HRPin2);
    analog_test_output1 = analogRead(HRPin1);
    analog_test_reference = analogRead(HRPinRef);

    if ( analog_test_output2 > 2000) {
        digitalWrite(led, HIGH);
    }
    if ( analog_test_output2 <= 2000) {
        digitalWrite(led, LOW);
    }
    //pin_blink_led(HRPin2, 2000, led);
    delayMicroseconds(50); // short to find peak
    

        
    
    
}

void pin_blink_led( PIN , VALUE, LED )
{
    ( analogRead(PIN) >= VALUE ) ? digitalWrite(LED, HIGH) && delay(500) : digitalWrite(LED, LOW);
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
