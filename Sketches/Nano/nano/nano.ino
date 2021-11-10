#include <SoftwareSerial.h>
SoftwareSerial btSerial(10,11);

//Bluetooth Vars
char command='9';
int btState=7;



//TEST LED
int led=4;
//ULTRASONIC
int trigger=8,echo=9;
long duration=0,distance=0;
long maxdist=50;
//Dead pins
int d1=5,d2=2;


//Control
bool detected=false;
bool startCheck=false;
bool endCheck=false;




void setup() {
  pinMode(led, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  //Ultrasonic
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  //Serial  
  pinMode(btState,INPUT);
  btSerial.begin(38400);
  Serial.begin(38400);
  Serial.println("Slave 1 is booting up");
  
}

// the loop function runs over and over again forever
void loop() {
  while(btSerial.available()>0){
      command=btSerial.read();
      Serial.print("Found command :");
      Serial.println(command); 
      btUpdate(command); 
      break;   
   }
  
  if(digitalRead(btState)==HIGH && startCheck==true){
    Serial.println("Bluetooth connected with start Check");
    digitalWrite(led,HIGH);
    delay(2000);
    long startTime=millis();
    long timeOut=startTime+5000;
    while((digitalRead(btState)==HIGH)&&(millis()<timeOut)){
      if(checkUltrasonic()<=maxdist){
        Serial.println("Detected Collision");       
        detected=true;
      }      
    }
    Serial.println("Serving master");
    if(detected==true){
      btSerial.write('1');      
    }
    else if(detected==false){
      btSerial.write('0');
    }
    startCheck=false;
    detected=false;     
  }
  
  
}

void btUpdate(char command){
  if(command=='1'){
    startCheck=true;
    endCheck=false;
  }
  if(command=='0'){
    startCheck=false;
    endCheck=true;
  }

}
