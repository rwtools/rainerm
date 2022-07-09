#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
//#include <freertos>//
#include <esp_now.h>
#include <WiFi.h>
//#include <echo.h>
#define BUTTON      3
#define LED         2
#define NUMPIXELS   1
int lastState = HIGH;
int currentState;  

int buttonCount = 1;
//byte* echoPins = new byte[echoCount] { 7, 6 };ECHO Declare //
byte trigPin1 = 10;
byte trigPin2 = 8;
byte echoPin1 = 4;
byte echoPin2 = 5;
float myping1;
float myping2;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
struct echo{
    int left;
    int right;
};
static QueueHandle_t queue;
float timeDuration, distance;
void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );