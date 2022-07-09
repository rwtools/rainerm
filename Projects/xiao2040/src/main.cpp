// Need to add watchdog self reset //
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
//#include <HCSR04.h>
#include <SSD1306Wire.h>
SSD1306Wire display(0x3c,6,7);

#define NUMPIXELS 1
byte triggerPin = 27;
byte echoPin = 26;

unsigned long timerStart = 0;
int TIMER_TRIGGER_HIGH = 10;
int TIMER_LOW_HIGH = 2;
int step;
float timeDuration, distance;
/*The states of an ultrasonic sensor*/
enum SensorStates {
  TRIG_LOW,
  TRIG_HIGH,
  ECHO_HIGH
};
SensorStates _sensorState = TRIG_LOW;
void startTimer() {
  timerStart = millis();
}
 
bool isTimerReady(int mSec) {
  return (millis() - timerStart) < mSec;
}
byte boardLED = 18;    //25;  //maybe pin 18
int myping;
int Power = 11;
int PIN  = 12;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//This is for Task on Core 1
//void setup1(){
//
//}
//void loop1(){
//
//}
// End Core 1
void setup() {
    Serial.begin(115200);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
   display.init();
   //display.flipScreenVertically();
   display.resetOrientation();
   display.setFont(ArialMT_Plain_10);
   display.setTextAlignment(TEXT_ALIGN_LEFT);
    
    pixels.begin();
    pinMode(Power,OUTPUT);
    digitalWrite(Power, HIGH);
    
    
}

void loop(){
         pixels.clear();
      
      /*Switch between the ultrasonic sensor states*/
  switch (_sensorState) {
    /* Start with LOW pulse to ensure a clean HIGH pulse*/
    case TRIG_LOW: {
        digitalWrite(triggerPin, LOW);
        startTimer();
        if (isTimerReady(TIMER_LOW_HIGH)) {
          _sensorState = TRIG_HIGH;
        }
      } break;
      
    /*Triggered a HIGH pulse of 10 microseconds*/
    case TRIG_HIGH: {
        digitalWrite(triggerPin, HIGH);
        startTimer();
        if (isTimerReady(TIMER_TRIGGER_HIGH)) {
          _sensorState = ECHO_HIGH;
        }
      } break;
 
    /*Measures the time that ping took to return to the receiver.*/
    case ECHO_HIGH: {
        digitalWrite(triggerPin, LOW);
        timeDuration = pulseIn(echoPin, HIGH);
        /*
           distance = time * speed of sound
           speed of sound is 340 m/s => 0.034 cm/us
        */
        //Serial.print("Distance measured is: ");
        //Serial.print(timeDuration * 0.034 / 2);
        //Serial.println(" cm");
        _sensorState = TRIG_LOW;
      } break;
      
  }//end switch
         myping = timeDuration * 0.034 / 2;
               
           if (myping < 30){ 
           pixels.setPixelColor(0, pixels.Color(0, 0,255));
           pixels.show(); }
          
           if (myping > 500){
           pixels.setPixelColor(0, pixels.Color(0,255,255));
           pixels.show();}
    
               if (myping < 500){
           pixels.setPixelColor(0, pixels.Color(255,0,0));
           pixels.show();}
         
   
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, "Dist :" + String(myping));
    display.drawString(0, 20, "step :" + String(step));
  display.display();
    Serial.println("Test New");
   delay(100);
  

}