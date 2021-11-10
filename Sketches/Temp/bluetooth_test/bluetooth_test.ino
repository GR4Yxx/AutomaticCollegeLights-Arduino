#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);//tx/rx

void setup(){
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
