#include <Arduino.h>
#include <SoftwareSerial.h>
//Bluetooth
#define RX 11
#define TX 10
#define btStatus 7
SoftwareSerial btSerial(TX,RX);
//Indicator LED
#define led 4
//Ultrasonic sensor
#define trigger 8
#define echo 9
int duration=0,maxDistance=50;
long distance=0;
//relay
#define relay 9999

//conditions
bool btConnected=false;
bool awake=true;
int command=99;




void setup() {
  btSerial.begin(38400);
  Serial.begin(38400);
  //bluetooth
  pinMode(btStatus,INPUT);
  //indicator
  pinMode(led,OUTPUT);
  //Ultrasonic
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  digitalWrite(led,HIGH);
  delay(2000);
  digitalWrite(led,LOW);

}

void loop() {
  Serial.println("Waiting for commands");
  while(btConnected==true){    
      if(btSerial.available()){
          command=btSerial.read();
          Serial.print("Found command :");
          Serial.println(command);
          if(command=='x'){
            digitalWrite(led,HIGH);            
            awake=true;
            while(awake){
              if(checkUltrasonic()<maxDistance){
                Serial.println("Collision Detected");
                digitalWrite(led,LOW);
                btSerial.write('z');                                  
                awake=false;             
              }              
            }
         
          }
        } 
    
   if(digitalRead(btStatus)==LOW){
     Serial.println("DISCONNECTED");
     btConnected=false;    
  }    
  }
  btConnected=false;
  if(digitalRead(btStatus)==HIGH){
   Serial.println("CONNECTED");
   btConnected=true;    
  }
}

long checkUltrasonic(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration=pulseIn(echo,HIGH);
  distance= Distance(duration);
  Serial.print("Distance =");
  Serial.print(distance);
  Serial.println(" cm");  
  return distance;
  

  delay(1000);
}

long Distance(long time){ 
  long DistanceCalc;
   DistanceCalc=((time * 0.034)/2);
   return DistanceCalc;
  
}
