#include <SoftwareSerial.h>
SoftwareSerial BTSerial(5,16);//tx/rx

int btPower=4,btMode=0,btState=2;

int pir=14,ldr=A0;

char command='9';
int ldrDark=5;
bool btConnected=false;

void setup(){
  delay(5000);
  BTSerial.begin(38400);
  Serial.begin(38400);

  pinMode(ldr,INPUT);
  pinMode(pir,INPUT);

  pinMode(btPower,OUTPUT);
  pinMode(btMode,OUTPUT);
  pinMode(btState,INPUT);
  delay(2000);
  digitalWrite(btPower,HIGH);
  Serial.println("All Systems Starting....");
  delay(5000);
  //BTSerial.write("AT+BIND=0019,10,0837A2\r\n");
  
  
  
}

void loop(){ 
  
  if(checkLDR() && checkPIR()){
    Serial.println("Motion Detected...Checking Slave 1");
    pairS1();
    delay(5000);
    Serial.println("Sending start check");
    BTSerial.write(1);
    delay(2000);
    while(digitalRead(btState)==HIGH){
      if(BTSerial.available()>0){
        command=BTSerial.read();
        Serial.print("Found command :");
        Serial.println(command);        
        if(command=='0' || command=='1'){          
          btUpdate(command);
          break;
        }  
      }      
    }
    
  }
}

void btUpdate(int command){
  if(command=='1'){
    Serial.println("Human Detected");
  }
  else if(command='0'){
    Serial.println("Nothing Detected...Time to sleep...");
  } 
}










void pairS1(){
  startAT();
  Serial.println("sending AT for S1");
  //sendAT("AT+ROLE=1\r\n");
  sendAT("AT+BIND=0019,10,0840C3\r\n");
  delay(2000);
  startPair();
  Serial.println(" to s1");
  
}

void pairS2(){
  startAT();
  Serial.println("sending AT for S2");
  //sendAT("AT+ROLE=1\r\n");
  sendAT("AT+BIND=0019,10,0837A2\r\n");
  delay(2000);
  startPair();
  Serial.println("Paired to s2");
  
}

void startAT(){
  Serial.println("Started AT mode");
  digitalWrite(btPower,LOW);
  digitalWrite(btMode,HIGH);
  delay(2000);
  digitalWrite(btPower,HIGH);
  delay(5000);
}

void startPair(){
  bool btConnected=false;
  Serial.println("Started Pair mode");
  digitalWrite(btPower,LOW);
  digitalWrite(btMode,LOW);
  delay(2000);
  digitalWrite(btPower,HIGH);
  delay(5000);
  if(digitalRead(btState)==LOW){
      Serial.println("Not Paired...Attempting to Pair");      
  }
  delay(10000);  
  if(digitalRead(btState)==HIGH){
      Serial.print("Paired");      
  }
  else{
    Serial.print("Not Paired");
    
  }
      
}


void sendAT(const char* Stringx){
  delay(2000);
  Serial.println(Stringx);
  BTSerial.write(Stringx);
  while(BTSerial.available()){
    Serial.write((BTSerial.read()));
    
  }
  while(Serial.available()){
    BTSerial.write((Serial.read()));
  }
  
}

bool checkPIR(){
  long state = digitalRead(pir);
  if(state == HIGH) {
      //Serial.println("Motion detected!");
      return true;
    }
    else {
      return false;
    } 
    
}

bool checkLDR(){
  int ldrStatus = analogRead(ldr)/10;
  //Serial.print(ldrStatus);

  if(ldrStatus > ldrDark){
    return false;
  }

  if(ldrStatus <=ldrDark) {
    return true;
  }
  
  
}
