#include <SoftwareSerial.h>
SoftwareSerial BTSerial(5,16);//tx/rx
int btPower=4,btMode=0,btState=2;
void setup(){

  pinMode(btPower,OUTPUT);
  pinMode(btMode,OUTPUT);
  pinMode(btState,INPUT);
  digitalWrite(btMode,LOW);
  delay(2000);
  digitalWrite(btPower,HIGH);
  
  BTSerial.begin(38400);
  Serial.begin(38400);
  Serial.println("Enter AT Commands");
  
}

void loop(){
  if(BTSerial.available()){
    Serial.write((BTSerial.read()));
    
  }
  if(Serial.available()){
    BTSerial.write((Serial.read()));
  }
}
