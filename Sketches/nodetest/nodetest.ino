#include <SoftwareSerial.h>
SoftwareSerial BTSerial(5,16);//tx/rx

int btPower=4,btMode=0,btState=2;

bool btConnected=false;

void setup(){
  delay(5000);
  BTSerial.begin(38400);
  Serial.begin(38400);

  pinMode(btPower,OUTPUT);
  pinMode(btMode,OUTPUT);
  pinMode(btState,INPUT);
  delay(2000);
  digitalWrite(btPower,HIGH);
  Serial.println("Enter AT Commands");
  delay(5000);
  //BTSerial.write("AT+BIND=0019,10,0837A2\r\n");
  
  
  
}

void loop(){ 
  Serial.println("Pairing to S1");
  pairS1();
  delay(10000);
  Serial.println("Pairing to S2");
  pairS2();
  delay(10000);
  
  if(BTSerial.available()){
    Serial.write((BTSerial.read()));
    
  }
  if(Serial.available()){
    BTSerial.write((Serial.read()));
  }


}

void pairS1(){
  startAT();
  sendAT("AT+ROLE=1\r\n");
  sendAT("AT+BIND=0019,10,0840C3\r\n");
  delay(2000);
  startPair();
  Serial.println("Paired to s1");
  
}

void pairS2(){
  startAT();
  sendAT("AT+ROLE=1\r\n");
  sendAT("AT+BIND=0019,10,0837A2\r\n");
  delay(2000);
  startPair();
  Serial.println("Paired to s2");
  
}





void startAT(){
  Serial.println("Started AT mode");
  delay(2000);
  digitalWrite(btPower,LOW);
  digitalWrite(btMode,HIGH);
  delay(2000);
  digitalWrite(btPower,HIGH);
  delay(7000);
}

void startPair(){
  bool btConnected=false;
  Serial.println("Started Pair mode");
  delay(2000);
  digitalWrite(btPower,LOW);
  digitalWrite(btMode,LOW);
  delay(2000);
  digitalWrite(btPower,HIGH);
  while(!btConnected){
    if(digitalRead(btState)==HIGH){
      btConnected=true;
    }
  }
  
}


void sendAT(const char* Stringx){
  delay(2000);
  Serial.println(Stringx);
  BTSerial.write(Stringx);
  if(BTSerial.available()){
    Serial.write((BTSerial.read()));
    
  }
  if(Serial.available()){
    BTSerial.write((Serial.read()));
  }
  
}
