#include <TMRpcm.h>
#include <pcmRF.h>
#include <pcmConfig.h>

//caution us
//left us
//obstacle ir
//light
//dark

#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;
int Calculate_Distance(int trigPin,int echoPin);
void play_recording( char  aud[],int distance,int trigPin,int echoPin);

int FacingFronttrigPin = 2;
int FacingFrontechoPin = 3;
int Frontdistance;
int FacingRighttrigPin = 4;
int FacingRightechoPin = 5;
int Rightdistance;
void setup()
{
  tmrpcm.speakerPin=9;
  
  if(!SD.begin(SD_ChipSelectPin))
  
    {
      Serial.println("SD fail");
      return;
    }
  
  pinMode(FacingFronttrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(FacingFrontechoPin, INPUT); // Sets the echoPin as an Input
  pinMode(FacingRighttrigPin, OUTPUT); 
  pinMode(FacingRightechoPin, INPUT);
  Serial.begin(9600); // Starts the serial communication
}

//sudo chmod a+rw /dev/ttyACM0


void loop() {

 Frontdistance=Calculate_Distance(FacingFronttrigPin,FacingFrontechoPin);
  //Frontdistance= Calculate_Distance( FacingFronttrigPin, );
  Serial.print("FRONT DISTANCE " );
   Serial.println(Frontdistance);
 // delay(750);
  if( Frontdistance < 5 )
    {
     
       Serial.println("FRONT DISTANCE less than 5 ");
      char  aud[]="caution.wav";
       play_recording(aud,Rightdistance,FacingRighttrigPin, FacingRightechoPin);
    }
    
  Rightdistance= Calculate_Distance( FacingRighttrigPin, FacingRightechoPin);
   if( Rightdistance < 5 )
    {
      Serial.println("RIGHT DISTANCE less than 5");
     
    char    aud[]="left.wav";
     play_recording(aud,Rightdistance,FacingRighttrigPin, FacingRightechoPin);
    } 

    
    delay(750);
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


int Calculate_Distance(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(3000);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance= duration*0.034/2;
  return distance;
}


