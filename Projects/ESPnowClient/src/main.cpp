#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#define LED         10 //old 2
#define NUMPIXELS  4   //old 1
//#include "WiFi.h"
Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_RGB + NEO_KHZ800);
#define LED2         2
#define NUMPIXELS2   1
//int lastState = HIGH;
//int currentState;  
//int buttonCount = 1;
#include <esp_now.h>
#include <WiFi.h>
int dataleft;
int dataright; 
// Define a data structure
typedef struct struct_message {
   int b;
   int c;
 
} struct_message;
 
// Create a structured object
struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  dataleft=myData.b;
  dataright=myData.c;
   
}
void life( void * parameter ){
    Adafruit_NeoPixel pixels(NUMPIXELS2, LED2, NEO_RGB + NEO_KHZ800);
       while (1) {  
                 pixels.clear();     
                 pixels.show();
                delay(1000);      
                pixels.setPixelColor(0, pixels.Color(255,0,0));
                pixels.show();   
                delay(1000);
                }   
}
//////////////////////////////////////////////////////////////////////////////
  void blink(void * parameter) {

            for(;;){  
               pixels.clear();       
                   
               pixels.show();
                
            if (dataleft > 25 && dataleft < 300){                   
                  
                pixels.setPixelColor(0, pixels.Color(0,255,0));                     
                               
                pixels.setPixelColor(1, pixels.Color(0,255,0)); 
                pixels.show();
            }

            if (dataright > 25 && dataright < 300){                     
                 pixels.setPixelColor(2, pixels.Color(0,255, 0));
               
                 pixels.setPixelColor(3, pixels.Color(0,255,0));          
                 pixels.show();
            }
        
         }
 }
           

void setup() {

  Serial.begin(115200);
  pixels.begin();
    
  WiFi.mode(WIFI_STA);
   // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
  xTaskCreate(blink,"LED blink",2000,NULL,1,NULL);
  xTaskCreate(life,"LED blink",2000,NULL,1,NULL);        
}


void loop() {}
   
