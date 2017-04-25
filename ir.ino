#include <TMRpcm.h>
#include <pcmRF.h>
#include <pcmConfig.h>



#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;



int LED = 13; // Use the onboard Uno LED
int isObstaclePin = 7;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE


void play_recording(char aud[],int distance,int trigPin,int echoPin);
void setup() {

   tmrpcm.speakerPin=9;
  
  if(!SD.begin(SD_ChipSelectPin))
  
    {
      Serial.println("SD fail");
      return;
    }
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW)
  {
   // Serial.println("OBSTACLE!!, OBSTACLE!!");
    Serial.println("clear");
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    //Serial.println("clear");
    digitalWrite(LED, LOW);
  }
  delay(200);
}

void play_recording(char aud[],int distance,int trigPin,int echoPin){
  
  int newdist;
  
  tmrpcm.setVolume(6);
  tmrpcm.play(aud);
  
 
 delay(1000);
 if(tmrpcm.isPlaying()){
      Serial.println("playing");
      newdist=Calculate_Distance(trigPin,echoPin);
      Serial.println(newdist);
      delay(500);
     // Serial.println("new dist "+newdist);
      //if(newdist>=5){
       // delay(5000);
        /*Serial.println("pausing");
        tmrpcm.pause();
      }*/
  }

 
  
}
