#include <Adafruit_NeoPixel.h>
SemaphoreHandle_t xBinarySemaphore;
int counter2;
int counter1;
int left1;
int right1;
Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);
//SemaphoreHandle_t xSerialSemaphore = 0;
void echo1( void * parameter )
{
   //SemaphoreHandle_t xBinarySemaphore;
   while (1) 
    
    {
  xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(15);  
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(25);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);   
  float distanceCm1 = duration1 * SOUND_SPEED/2;
  if (distanceCm1 > 25 && distanceCm1 < 300){
          
         left1 = distanceCm1;
              }
   else { 
           left1 = distanceCm1;
        }         
  xSemaphoreGive(xBinarySemaphore);
        delay(40); 
   
    }
  
 
}

void echo2( void * parameter )
{
  while (1)
    
    {
   xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(15);  
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(25);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);   
  float distanceCm2 = duration2 * SOUND_SPEED/2;
     if (distanceCm2 > 25 && distanceCm2 < 300){
          
         right1 = distanceCm2;
         }
     else { 
          right1=0; 
      }

         
         struct echo myecho;
         myecho.left= left1;
         myecho.right= right1;
         xQueueSend(queue, &myecho,100000);

      xSemaphoreGive(xBinarySemaphore);
        delay(40);  
    }
}    
    
void blink( void * parameter ){
   Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);
       while (1) {  
               pixels.clear();     
               pixels.show();
                     delay(1000);
      
                pixels.setPixelColor(0, pixels.Color(0,255,0));
                pixels.show();   
        delay(1000);//}
            }   
  
}
 
