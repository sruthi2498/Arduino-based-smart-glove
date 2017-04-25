#include <TMRpcm.h>
#include <pcmRF.h>
#include <pcmConfig.h>
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;


int isObstaclePin = 6;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE

int FacingFronttrigPin = 2;
int FacingFrontechoPin = 3;
int Frontdistance;
int FacingRighttrigPin = 4;
int FacingRightechoPin = 5;
int Rightdistance;

int sensorPin = 1;            
unsigned int sensorValue = 0;

void play_recording_ir(char aud[],int pin);
void play_recording(char aud[],int distance,int trigPin,int echoPin);
int Calculate_Distance(int trigPin,int echoPin);
void ultrasonic_sensor();
void IR_sensor();
void ldr();
void play_recording_ldr(char aud[],int pin);
int first_ldr=1;


//sudo chmod a+rw /dev/ttyACM0


void setup() {

   tmrpcm.speakerPin=9;
  
  if(!SD.begin(SD_ChipSelectPin))
  
    {
      Serial.println("SD fail");
      return;
    }
  pinMode(isObstaclePin, INPUT);

  pinMode(13, OUTPUT);
  pinMode(FacingFronttrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(FacingFrontechoPin, INPUT); // Sets the echoPin as an Input
  pinMode(FacingRighttrigPin, OUTPUT); 
  pinMode(FacingRightechoPin, INPUT); 
  Serial.begin(9600);

  
  
}

void loop() {
  if(first_ldr)ldr();
 // Serial.println("ok");
  while(1){
          //ldr();
         ultrasonic_sensor();
         IR_sensor();
    }
  
}
void IR_sensor(){

        isObstacle = digitalRead(isObstaclePin);
          int   pin=isObstacle;
          Serial.println(isObstacle);
          if (isObstacle == LOW)
          {
            Serial.println("clear");
            
          }
          else
          {
            Serial.println("OBSTACLE!!, OBSTACLE!!");
             char  aud[]="obstacle.wav";
             play_recording_ir(aud,pin);
            //Serial.println("clear");
            //digitalWrite(LED, LOW);
          }
          
          delay(200);
}


void ldr(){
     first_ldr=0;
          sensorValue = analogRead(sensorPin);    
          if(sensorValue<400) {
            Serial.println("ON");
             char  aud[]="light.wav";
            play_recording_ldr(aud,sensorPin);
          }
          else {
                Serial.println("OFF");
                 char  aud[]="dark.wav";
            play_recording_ldr(aud,sensorPin);
          }
          
     
}

void ultrasonic_sensor(){
         Frontdistance=Calculate_Distance(FacingFronttrigPin,FacingFrontechoPin);
          int flag=0;
           if(Frontdistance>40 || Frontdistance<=0) {flag=1;Serial.println("exceeded");}
           if(flag==0){
                  Serial.print("FRONT DISTANCE " );
                   Serial.println(Frontdistance);
                   
         
           
                  if( Frontdistance < 5  )
                    {
                     
                       Serial.println("FRONT DISTANCE less than 5 ");
                      char  aud[]="caution.wav";
                       play_recording(aud,Rightdistance,FacingRighttrigPin, FacingRightechoPin);
                    }
                  
              
        
           } 
             Rightdistance= Calculate_Distance( FacingRighttrigPin, FacingRightechoPin);
             int g=0;
             if(Rightdistance <=0) g=1;
             if(g==0){
                   Serial.print(" RIGHT DISTANCE " );
                  Serial.println(Rightdistance);
                   if( Rightdistance < 5 )
                    {
                      Serial.println("RIGHT DISTANCE less than 5");
                     
                    char aud[]="left.wav";
                     play_recording(aud,Rightdistance,FacingRighttrigPin, FacingRightechoPin);
                   } 
             }
            delay(1000);
}

void play_recording_ir(char aud[],int pin){
        
           if(tmrpcm.isPlaying())  {delay(2000);tmrpcm.pause();}
          int newdist;
          
          tmrpcm.setVolume(6);
          tmrpcm.play(aud);
          
         
         delay(1000);
         if(tmrpcm.isPlaying()){
              Serial.println("playing");
              delay(500);
              int newp= digitalRead(isObstaclePin);
              if (newp == LOW)
              {
                Serial.println("NO OBSTACLE");
                 tmrpcm.pause();
              }
          }
}

void play_recording_ldr(char aud[],int pin){
          
           if(tmrpcm.isPlaying())  {delay(2000);tmrpcm.pause();}
          int newdist;
         
              tmrpcm.setVolume(6);
              tmrpcm.play(aud);
          
         
         delay(1000);
         if(tmrpcm.isPlaying() ){
              Serial.println("playing");
              delay(500);
              int newp= digitalRead(isObstaclePin);
              if (newp == LOW)
              {
              //  Serial.println("NO OBSTACLE");
                 tmrpcm.pause();
              }
          }
}

void play_recording(char aud[],int distance,int trigPin,int echoPin){
           if(tmrpcm.isPlaying())  {delay(2000);tmrpcm.pause();}
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
