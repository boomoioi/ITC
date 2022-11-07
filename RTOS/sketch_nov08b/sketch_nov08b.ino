#include <Arduino_FreeRTOS.h>
#include "queue.h"
#define RED 13
#define YELLOW 12
#define GREEN 11
#define SW1 5
#define SW2 4
#define SW3 3
QueueHandle_t ledQueueG;
QueueHandle_t ledQueueR;
QueueHandle_t ledQueueY;

void setup(){
    Serial.begin(9600);
    ledQueueR =  xQueueCreate(5,sizeof(int32_t));
    ledQueueY =  xQueueCreate(5,sizeof(int32_t));
    ledQueueG =  xQueueCreate(5,sizeof(int32_t));
    xTaskCreate(vSenderTaskR,"Sender Task RED",100,NULL,1,NULL);
    xTaskCreate(vReceiverTaskR,"Receiver Task RED", 100,NULL, 1, NULL);
    xTaskCreate(vSenderTaskY,"Sender Task YELLOW",100,NULL,1,NULL);
    xTaskCreate(vReceiverTaskY,"Receiver Task YELLOW", 100,NULL, 1, NULL);
    xTaskCreate(vSenderTaskG,"Sender Task YELLOW",100,NULL,1,NULL);
    xTaskCreate(vReceiverTaskG,"Receiver Task YELLOW", 100,NULL, 1, NULL);
}

void vSenderTaskR(void *pvParameters){
    BaseType_t qStatus;
    int32_t valueToSend= 0;
    pinMode(SW1, INPUT);  
    while(1){
      valueToSend= digitalRead(SW1);
      qStatus= xQueueSend(ledQueueR,&valueToSend,0); 
      vTaskDelay(10);
    }
}

void vReceiverTaskR(void *pvParameters){
    int32_t valueReceived;
    BaseType_t qStatus;
    const TickType_t xTicksToWait= pdMS_TO_TICKS(100);
    pinMode(RED, OUTPUT); 
    unsigned long startTime;
    while(1){
      xQueueReceive(ledQueueR,&valueReceived,xTicksToWait);
      if(valueReceived==1){
        digitalWrite(RED, HIGH);
        startTime = millis();
      }
      if(millis()-startTime>=3000){
        digitalWrite(RED, LOW);
      }
    }
} 


void vSenderTaskY(void *pvParameters){
    BaseType_t qStatus;
    int32_t valueToSend= 0;
    pinMode(SW2, INPUT);  
    while(1){
      valueToSend= digitalRead(SW2);
      qStatus= xQueueSend(ledQueueY,&valueToSend,0); 
      vTaskDelay(10);
    }
}

void vReceiverTaskY(void *pvParameters){
    int32_t valueReceived;
    BaseType_t qStatus;
    const TickType_t xTicksToWait= pdMS_TO_TICKS(100);
    pinMode(YELLOW, OUTPUT); 
    unsigned long startBlink; 
    unsigned long startTime=0; 
    int blinkCheck = 0;
    while(1){
      xQueueReceive(ledQueueY,&valueReceived,xTicksToWait);
      if(valueReceived == 1 && millis()-startTime>500){
           blinkCheck = !blinkCheck;
           startTime = millis();
           startBlink = millis();
           digitalWrite(YELLOW, HIGH);
      }
      if(blinkCheck == 1){
        if(millis()-startBlink >= 200){
            digitalWrite(YELLOW, !digitalRead(YELLOW));
            startBlink = millis();
        }
      } else {
        digitalWrite(YELLOW, LOW);
      }
      vTaskDelay(10);
    }
}

void vSenderTaskG(void *pvParameters){
    BaseType_t qStatus;
    int32_t valueToSend= 0;
    pinMode(SW3, INPUT);  
    unsigned long startTime=0;
    while(1){
      valueToSend= digitalRead(SW3);
      qStatus= xQueueSend(ledQueueG,&valueToSend,0); 
      valueToSend=0;
      vTaskDelay(10);
    }
}

void vReceiverTaskG(void *pvParameters){
    int32_t valueReceived;
    BaseType_t qStatus;
    const TickType_t xTicksToWait= pdMS_TO_TICKS(100);
    pinMode(GREEN, OUTPUT); 
    unsigned long startBlink; 
    unsigned long startTime;
    int check = 1;
    while(1){
      xQueueReceive(ledQueueG,&valueReceived,xTicksToWait);
      if(valueReceived==1 and check){
        startTime = millis();
        startBlink = millis();
        digitalWrite(GREEN, HIGH);
        check = 0;
      }      
      if(millis()-startTime>=3000){
        digitalWrite(GREEN, LOW);
        check = 1;
      } else {
        if(millis()-startBlink >= 500){
          digitalWrite(GREEN, !digitalRead(GREEN));
          startBlink = millis();
        }
      }
      vTaskDelay(1);
    }
}
void loop(){
  
}
