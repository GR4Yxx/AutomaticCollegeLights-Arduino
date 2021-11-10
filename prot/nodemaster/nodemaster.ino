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
  
  while(btConnected==true){
    if(checkUltrasonic()<maxDistance){
      Serial.println("Collision Detected");
      digitalWrite(led,HIGH);
      btSerial.write('1');       
        delay(1000);
      awake=true;
      Serial.println("Waiting for commands");
      while(awake){        
        if(btSerial.available()>0){
          command=btSerial.read();
          Serial.print("Found command :");
          Serial.println(command);
          if(command!='0'){
            digitalWrite(led,LOW);
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
