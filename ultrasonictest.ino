int Calculate_Distance(int trigPin,int echoPin);

int FacingFronttrigPin = 9;
int FacingFrontechoPin = 10;
int Frontdistance;
int FacingRighttrigPin = 11;
int FacingRightechoPin = 12;
int Rightdistance;

void setup() {
pinMode(FacingFronttrigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(FacingFrontechoPin, INPUT); // Sets the echoPin as an Input
pinMode(FacingRighttrigPin, OUTPUT); 
pinMode(FacingRightechoPin, INPUT);
Serial.begin(9600); // Starts the serial communication
}
void loop() {
  
  Frontdistance= Calculate_Distance( FacingFronttrigPin, FacingFrontechoPin);
 
  delay(100);
  if( Frontdistance < 50 )
    {
       Serial.println("FRONT DISTANCE less than 50 ");
    }
  Rightdistance= Calculate_Distance( FacingRighttrigPin, FacingRightechoPin);
   //delay(750);
 if( Rightdistance < 50 )
    {
      Serial.println("RIGHT DISTANCE less than 50 ");
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


