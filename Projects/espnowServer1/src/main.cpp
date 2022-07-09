#include <main.h>
#include <echo.h>

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = { 0x34, 0xB4, 0x72, 0x7F, 0xED, 0x70 };

// Define a data structure
struct struct_message {
    int b;
    int c;
    }
struct_message;
//myData;
//Create a structured object
//struct_message myData;
/// Peer info
esp_now_peer_info_t peerInfo;
// Callback function called when data is sent
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
    //Serial.print("\r\nLast Packet Send Status:\t");
    //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}



void setup() {
  // put your setup code here, to run once:
  pixels.begin();
    //pinMode(BUTTON, INPUT_PULLUP);
    // Set up Serial Monitor
    Serial.begin(115200);
    pinMode(trigPin1, OUTPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin1, INPUT_PULLUP);
    pinMode(echoPin2, INPUT_PULLUP);
    queue = xQueueCreate(1, sizeof(struct echo));
    // Set ESP32 as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Initilize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the send callback
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    ////////////////////////////////////////////
    xBinarySemaphore = xSemaphoreCreateBinary();     
    xTaskCreate(echo1,"TaskOne", 4000,NULL,1,NULL);                   
    xTaskCreate( echo2,"TaskOne",4000,NULL,1,NULL);
    xTaskCreate( blink,"blink",4000,NULL,1,NULL);
    xSemaphoreGive(xBinarySemaphore);                          
 
     
}

void loop() {
  struct echo element;
   xQueueReceive(queue, &element,portMAX_DELAY);
   //Serial.print("Left:");
   int links= element.left;
   //Serial.println(element.left);
   //Serial.print("Right:");
   int rechts= element.right;
   //Serial.println(element.right);
  
    
    //bool_value = !bool_value;
        // Format structured data
    struct struct_message myData;    
    //strcpy(myData.a, "Welcome to the Workshop!");
    myData.b = links;
    myData.c = rechts;
    //myData.d = bool_value;

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*)&myData, sizeof(myData));

    if (result == ESP_OK) {
       // Serial.println("Sending confirmed");
    }
    else {
        Serial.println("Sending error");
    }
  
    
    
    delay(250);

}
